#include "Engine.h"

Didax::Engine::Engine()
{
}

Didax::Engine::Engine(const std::string& dataFilePath)
{
	init(dataFilePath);
}

void Didax::Engine::init(const std::string& dataFilePath)
{
	m_dataFilePath = dataFilePath;
}

bool Didax::Engine::run()
{
	if (!loadSettings())
		return false;
	if (!createWindow())
		return false;
	if (!loadAssets())
		return false;
	srand((unsigned int)(time(NULL)));
	m_clock.restart();
	while (m_window.getWindow().isOpen())
	{
		update();
		render();
		input();
	}
	return true;
}

Didax::Entity_ptr Didax::Engine::addEntity()
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::addEntity(const std::string& name)
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::getEntity(const std::string& name)
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::removeEntity(const std::string& name)
{
	return Entity_ptr();
}

float Didax::Engine::getDeltaTime() const
{
	return m_deltaT;
}

void Didax::Engine::setCameraPosition(float x, float y)
{
}

void Didax::Engine::setCameraPosition(const sf::Vector2f& p)
{
}

sf::Vector2f Didax::Engine::getCameraPosition() const
{
	return sf::Vector2f();
}

void Didax::Engine::setCameraSize(float w, float h)
{
}

void Didax::Engine::setCameraSize(const sf::Vector2f& p)
{
}

sf::Vector2f Didax::Engine::getCameraSize() const
{
	return sf::Vector2f();
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

	// TO DO
	}
}

void Didax::Engine::update()
{
	auto time = m_clock.getElapsedTime();
	m_clock.restart();
	m_deltaT = time.asSeconds();

	// TO DO
}

void Didax::Engine::render()
{
	m_window.getWindow().clear(sf::Color{ 255,255,255,255 });

	// TO Do

	m_window.render();
}
