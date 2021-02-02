#include "Window.h"

Didax::Window::Window() : m_windowStyle{ 0 }
{
}

void Didax::Window::init(const WindowConfig& config)
{
	m_videoMode = config.m_mode;
	m_windowStyle = config.m_windowStyle;
	if (m_windowStyle == sf::Style::Fullscreen)
		m_videoMode = sf::VideoMode::getFullscreenModes()[0];
	m_rezolution = sf::Vector2i{ (int)m_videoMode.width, (int)m_videoMode.height };
	recreate();
}

sf::RenderWindow& Didax::Window::getWindow()
{
	return m_window;
}

const sf::RenderWindow& Didax::Window::getWindow() const
{
	return m_window;
}

sf::VideoMode Didax::Window::getVideoMode()
{
	return m_videoMode;
}

void Didax::Window::setVideoMode(const sf::VideoMode& mode)
{
	m_videoMode = mode;
	recreate();
}

const std::string& Didax::Window::getTitle() const
{
	return m_title;
}

void Didax::Window::setTitle(const std::string& title)
{
	m_title = title;
	m_window.setTitle(title);
}

bool Didax::Window::getFoolscreen() const
{
	return (m_windowStyle & sf::Style::Fullscreen);
}

void Didax::Window::setFoolscreen(bool state)
{
	if (state)
		m_windowStyle = sf::Style::Fullscreen;
	else
		m_windowStyle = sf::Style::Default;

	recreate();
}

sf::Vector2i Didax::Window::getRezolution()const
{
	return m_rezolution;
}

void Didax::Window::setRezolution(const sf::Vector2i& rezolution)
{
	m_rezolution = rezolution;
	recreate();
}

void Didax::Window::recreate()
{
	m_window.create(m_videoMode, m_title, m_windowStyle);
}

void Didax::Window::render()
{
	m_window.display();
}

void Didax::Window::processEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		m_window.close();
}

void Didax::Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	m_window.draw(drawable, states);
}
