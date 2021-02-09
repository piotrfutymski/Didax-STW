#include "Engine.h"

Didax::Engine::Engine()
{
}

Didax::Engine::Engine(const std::string& dataFilePath)
{
	init(dataFilePath);
}

bool Didax::Engine::init(const std::string& dataFilePath)
{
	m_dataFilePath = dataFilePath;
	if (!loadSettings())
		return false;
	if (!createWindow())
		return false;
	if (!loadAssets())
		return false;
	srand((unsigned int)(time(NULL)));
	return true;
}

void Didax::Engine::run()
{
	m_clock.restart();
	while (m_window.getWindow().isOpen())
	{
		update();
		render();
		input();
		if (m_close)
			m_window.getWindow().close();
	}
	Logger::close();
}

void Didax::Engine::setOwnCursor(const std::string& def, const std::string& hand, const std::string& load)
{
	auto t1 = m_assets.getAsset<TextureAsset>(def);
	if (t1 == nullptr)
	{
		Logger::log("Texture with name '" + def + "' is not loaded");
		return;
	}
	auto t2 = m_assets.getAsset<TextureAsset>(hand);
	if (t2 == nullptr)
	{
		Logger::log("Texture with name '" + hand + "' is not loaded");
		return;
	}
	auto t3 = m_assets.getAsset<TextureAsset>(load);
	if (t3 == nullptr)
	{
		Logger::log("Texture with name '" + load + "' is not loaded");
		return;
	}
	m_window.getWindow().setMouseCursorVisible(false);
	Input::setCursorTexture(Input::CursorState::Standard, &t1->texture);
	Input::setCursorTexture(Input::CursorState::Click, &t2->texture);
	Input::setCursorTexture(Input::CursorState::Loading, &t3->texture);
	Input::setCursor(Input::CursorState::Standard);
	m_ownCursor = true;
}

Didax::Entity_ptr Didax::Engine::addEntity()
{
	auto name = getNextName();
	return addEntity(name);
}

Didax::Entity_ptr Didax::Engine::addEntity(const std::string& name)
{
	return addEntity<VoidScript>(name);
}

Didax::Entity_ptr Didax::Engine::getEntity(const std::string& name)
{
	return  m_entities[name].get();
}

Didax::Entity_ptr Didax::Engine::removeEntity(const std::string& name)
{
	m_entities[name]->setToKill();
	auto w = m_entities[name]->getWidget();
	if (w != nullptr)
	{
		for (auto c : w->getChildren())
			c->getEntity()->setToKill();
		if (w->getParent() != nullptr)
			w->getParent()->removeChild(w);

	}
	return m_entities[name].get();
}

float Didax::Engine::getDeltaTime() const
{
	return m_deltaT;
}

void Didax::Engine::setCameraPosition(float x, float y)
{
	setCameraPosition({ x,y });
}

void Didax::Engine::setCameraPosition(const sf::Vector2f& p)
{
	auto vi = m_window.getWindow().getView();
	vi.setCenter(p);
	m_window.getWindow().setView(vi);
}

void Didax::Engine::moveCamera(const sf::Vector2f& d)
{
	setCameraPosition(getCameraPosition() + d);
}

sf::Vector2f Didax::Engine::getCameraPosition() const
{
	return m_window.getWindow().getView().getCenter();
}

void Didax::Engine::setCameraSize(float w, float h)
{
	setCameraSize({ w,h });
}

void Didax::Engine::setCameraSize(const sf::Vector2f& p)
{
	auto vi = m_window.getWindow().getView();
	vi.setSize(p);
	m_window.getWindow().setView(vi);
}

sf::Vector2f Didax::Engine::getCameraSize() const
{
	return m_window.getWindow().getView().getSize();
}

Didax::AssetManager* Didax::Engine::getAssets()
{
	return &m_assets;
}

bool Didax::Engine::loadSettings()
{
	try {
		m_settings = std::move(DataLoader::loadJsonFromFile(m_dataFilePath));
	}
	catch (std::exception&) {
#ifdef _DEBUG
		std::cout << "Unable to load setting file" << std::endl;
#endif // DEBUG	
		return false;
	}
	return true;
}

bool Didax::Engine::createWindow()
{
	WindowConfig configuration;
	if (!configuration.init(m_settings))
	{
#ifdef _DEBUG
		std::cout << "Unable to read configuration from setting file" << std::endl;
#endif // _DEBUG
		return false;
	}
	m_window.init(configuration);
	Input::setWindow(&m_window.getWindow());
	m_window.getWindow().setVisible(true);
	m_window.getWindow().setActive(true);
	return true;
}

bool Didax::Engine::loadAssets()
{
	try {
		if (m_settings["assetPacked"])
			m_assets.loadAssets(m_settings["assetsFileBin"], true);
		else
			m_assets.loadAssets(m_settings["assetsFileRaw"], false);
	}
	catch (const std::exception&) {
#ifdef _DEBUG
		std::cout << "Unable to load assets" << std::endl;
#endif // _DEBUG
		return false;
	}
	return true;
}

void Didax::Engine::input()
{
	sf::Event event;
	while (m_window.getWindow().pollEvent(event))
	{
		m_window.processEvent(event);
#ifdef _DEBUG
		if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Escape)
			m_window.getWindow().close();
#endif // DEBUG

		for (auto& name : m_priortyQueue)
			m_entities[name]->input(event);
	}
}

void Didax::Engine::update()
{
	auto time = m_clock.getElapsedTime();
	m_clock.restart();
	m_deltaT = time.asSeconds();
	debClock -= m_deltaT;
	if (debClock < 0)
	{
		std::cout << "Frames: " + std::to_string((int)(1.0f / m_deltaT)) << std::endl;
		debClock = 1.0f;
	}		

	for (auto& name : m_entitiesAdded)
		m_priortyQueue.push_back(name);
	if (m_entitiesAdded.size() != 0)
		sortEntities();
	m_entitiesAdded = {};
	for (auto& name : m_priortyQueue)
		m_entities[name]->update(m_deltaT);	
	for (auto it = m_entities.begin(); it != m_entities.end(); )
	{
		if ((*it).second->getToKill())
		{
			(*it).second->kill();
			m_priortyQueue.erase(std::remove(m_priortyQueue.begin(), m_priortyQueue.end(), (*it).first), m_priortyQueue.end());
			it = m_entities.erase(it);			
		}
		else
			++it;
	}
}

void Didax::Engine::render()
{
	m_window.getWindow().clear(sf::Color{ 255,255,255,255 });

	for (auto it = m_priortyQueue.rbegin(); it != m_priortyQueue.rend(); it++)
		m_window.getWindow().draw(*m_entities[*it]);
	if (m_ownCursor)
	{
		Input::moveCursor();
		m_window.getWindow().draw(*Input::getCursor());
	}

	m_window.render();
}

std::string Didax::Engine::getNextName()
{
	return "Entity_" + std::to_string(ID++);
}

void Didax::Engine::sortEntities()
{
	std::sort(m_priortyQueue.begin(), m_priortyQueue.end(), [&](auto& left, auto& right) {
		return m_entities[left]->getPriority() > m_entities[right]->getPriority();
	});
}

void Didax::Engine::close()
{
	m_close = true;
}
