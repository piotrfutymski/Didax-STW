#pragma once

#include <SFML/Graphics.hpp>

#include "WindowConfig.h"

namespace Didax
{

	class Window
	{
	public:

		Window();

		void init(const WindowConfig& config);

		sf::RenderWindow& getWindow();

		const sf::RenderWindow& getWindow()const;

		sf::VideoMode getVideoMode();

		void setVideoMode(const sf::VideoMode& mode);

		const std::string& getTitle()const;

		void setTitle(const std::string& title);

		bool getFoolscreen() const;

		void setFoolscreen(bool state);

		sf::Vector2i getRezolution()const;

		void setRezolution(const sf::Vector2i& rezolution);

		void recreate();

		void render();

		void processEvent(sf::Event event);

		void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	private:

		sf::VideoMode m_videoMode;

		std::string m_title;

		sf::Uint32 m_windowStyle;

		sf::RenderWindow m_window;

		sf::Vector2i m_rezolution;

	};

}

