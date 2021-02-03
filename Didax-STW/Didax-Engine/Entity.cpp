#include "Entity.h"
#include "Engine.h"

Didax::Entity::Entity(Engine* parent, const std::string& name) :m_parent(parent), m_name(name)
{
	m_assets = m_parent->getAssets();
}

void Didax::Entity::update(float dT)
{
	if (isActive())
	{
		m_script->update(dT);
		if (m_widget != nullptr)
			m_widget->update(dT);
	}
}

void Didax::Entity::input(const sf::Event& evt)
{
	if (isActive())
	{
		m_script->input(evt);
		if (m_widget != nullptr)
			m_widget->input(evt);
	}
}

void Didax::Entity::kill()
{
	if (isActive())
		m_script->kill();
}

void Didax::Entity::start()
{
	if (isActive())
		m_script->start();
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

bool Didax::Entity::isVisible() const
{
	return m_isVisible;
}

void Didax::Entity::setVisible(bool v)
{
	m_isVisible = v;
}

int Didax::Entity::getPriority() const
{
	return m_priority;
}

void Didax::Entity::setPrority(int p)
{
	m_priority = p;
	m_parent->sortEntities();
}

bool Didax::Entity::isActive() const
{
	return m_isActive;
}

void Didax::Entity::setActive(bool a)
{
	m_isActive = a;
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
