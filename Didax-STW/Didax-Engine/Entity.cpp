#include "Entity.h"
#include "Engine.h"

Didax::Entity::Entity(Engine* parent, const std::string& name) :m_parent(parent), m_name(name)
{
	m_assets = m_parent->getAssets();
}

void Didax::Entity::update(float dT)
{
	m_script->update(dT);
	if (m_widget != nullptr)
		m_widget->update(dT);
}

void Didax::Entity::input(const sf::Event& evt)
{
	m_script->input(evt);
	if (m_widget != nullptr)
		m_widget->input(evt);
}

void Didax::Entity::kill()
{
	m_script->kill();
}

void Didax::Entity::start()
{
	m_script->start();
}

Didax::Widget* Didax::Entity::createWidget(const std::string& name, int priority)
{
	try {
		m_widget = WidgetJsonLoader::create(name, m_assets, m_parent, priority, this);
		setPriority(priority);
	}catch (const std::exception& e){
		std::string E = e.what();
		Logger::log("Can't create widget - reason: " + E);
		return nullptr;
	}	
	return m_widget.get();
}

void Didax::Entity::removeWidget()
{
	m_widget = nullptr;
}

bool Didax::Entity::getToKill() const
{
	return m_toKill;
}

void Didax::Entity::setToKill()
{
	m_toKill = true;
}

int Didax::Entity::getPriority() const
{
	return m_priority;
}

void Didax::Entity::setPriority(int p)
{
	m_priority = p;
	m_parent->sortEntities();
}

std::string Didax::Entity::getName() const
{
	return m_name;
}

void Didax::Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_widget != nullptr)
		target.draw(*(m_widget.get()), states);
}
