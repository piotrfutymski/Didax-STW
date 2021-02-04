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

void Didax::Input::setCursorTexture(CursorState s, sf::Texture* t)
{
	m_textures[(int)(s)] = t;
}

void Didax::Input::setCursor(CursorState s)
{
	if (m_textures[(int)(s)] != nullptr)
		m_cursor.setTexture(*m_textures[(int)(s)]);
}

void Didax::Input::moveCursor()
{
	auto m = getMousePosition();
	m_cursor.setPosition(m.x, m.y);
}

sf::Sprite* Didax::Input::getCursor()
{
	return &m_cursor;
}

sf::Window* Didax::Input::m_window = nullptr;

sf::Sprite  Didax::Input::m_cursor{};

sf::Texture* Didax::Input::m_textures[3]{nullptr, nullptr, nullptr};