#include "Canvas.h"

Didax::Canvas::Canvas(AssetManager* a):Widget(a)
{
}

void Didax::Canvas::setTexture(const std::string& name)
{
	auto t = m_assets->getAsset<TextureAsset>(name);
	if (t == nullptr)
	{
#ifdef _DEBUG
		std::cout << "Asset with name: " + name + " is not loaded" << std::endl;
#endif // _DEBUG
		return;
	}
	m_backgroundSprite.setTexture(t->texture);
	m_bType = BackgroundType::Image;
	updateSize();
}

void Didax::Canvas::setRect()
{
	m_bType = BackgroundType::Rect;
	updateSize();
}

void Didax::Canvas::unsetBackground()
{
	m_bType = BackgroundType::None;
}

void Didax::Canvas::_update(float deltaT)
{
}

void Didax::Canvas::_input(const sf::Event& event)
{
}

void Didax::Canvas::_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bType == BackgroundType::Image)
		target.draw(m_backgroundSprite, states);
	else if (m_bType == BackgroundType::Rect)
		target.draw(m_backgroundRect, states);
}

void Didax::Canvas::updatePosition()
{
	m_backgroundSprite.setPosition(m_absolute_position);
	m_backgroundRect.setPosition(m_absolute_position);
}

void Didax::Canvas::updateSize()
{
	if (m_bType == BackgroundType::Image)
	{
		auto textureSize = m_backgroundSprite.getTexture()->getSize();
		m_backgroundSprite.setScale({ m_size.x / textureSize.x, m_size.y / textureSize.y });
	}
	else if (m_bType == BackgroundType::Rect)
		m_backgroundRect.setSize(m_size);
}

void Didax::Canvas::updateColor()
{
	m_backgroundRect.setFillColor(m_color);
	m_backgroundSprite.setColor(m_color);
}
