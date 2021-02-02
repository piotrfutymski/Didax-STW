#include "Input.h"

void Didax::Input::setWindow(sf::Window* w)
{
	m_window = w;
}

sf::Vector2i Didax::Input::getMousePosition()
{
	return sf::Mouse::getPosition(*m_window);
}

sf::Vector2i Didax::Input::getRezolution()
{
	return (sf::Vector2i) m_window->getSize();
}

sf::Window* Didax::Input::m_window = nullptr;