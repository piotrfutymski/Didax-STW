#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

namespace Didax
{

	class Input
	{
	public:

		enum class CursorState {
			Standard, Click, Loading
		};

		static void setWindow(sf::Window* w);

		static sf::Vector2i getMousePosition();

		static sf::Vector2i getRezolution();

		static void setCursorTexture(CursorState s, sf::Texture* t);

		static void setCursor(CursorState s);

		static void moveCursor();

		static void update();

		static sf::Sprite* getCursor();

	private:

		static sf::Window* m_window;

		static sf::Sprite m_cursor;

		static sf::Texture*  m_textures[3];

		static sf::Vector2i m_mousePos;



	};

}
