#include "Button.h"

Didax::Button::Button(AssetManager* a, Entity*e):Widget(a,e)
{
}

void Didax::Button::setTexture(const std::string& name)
{
	auto t = m_assets->getAsset<TextureAsset>(name);
	if (t == nullptr)
	{
		Logger::log("Texture with name '" + name + "' is not loaded");
		return;
	}
	m_sprite.setTexture(t->texture);
	m_textureSet = true;
	updateSize();
}

void Didax::Button::setHoverMask(const sf::Color& c)
{
	m_hoverColorMask = c;
	this->updateColor();
}

void Didax::Button::setClickedMask(const sf::Color& c)
{
	m_clickedColorMask = c;
	this->updateColor();
}

void Didax::Button::setStandardMask(const sf::Color& c)
{
	m_standardColorMask = c;
	this->updateColor();
}

sf::Color Didax::Button::getHoverMask() const
{
	return m_hoverColorMask;
}

sf::Color Didax::Button::getClickedMask() const
{
	return m_clickedColorMask;
}

sf::Color Didax::Button::getStandardMask() const
{
	return m_standardColorMask;
}

void Didax::Button::_update(float deltaT)
{
	for (auto& c : m_callbacks)
	{
		if (c == Widget::CallbackType::onHoverIn || c == Widget::CallbackType::onHoverOut ||
			c == Widget::CallbackType::onPress || c == Widget::CallbackType::onRelease)
		{
			this->updateColor();
			if (c == Widget::CallbackType::onHoverIn)
				Input::setCursor(Input::CursorState::Click);
			if (c == Widget::CallbackType::onHoverOut)
				Input::setCursor(Input::CursorState::Standard);
			break;
		}
	}
}

void Didax::Button::_input(const sf::Event& event)
{
}

void Didax::Button::_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Didax::Button::updatePosition()
{
	m_sprite.setPosition(m_absolute_position);
}

void Didax::Button::updateSize()
{
	if (!m_textureSet)
		return;
	auto textureSize = m_sprite.getTexture()->getSize();
	m_sprite.setScale({ m_size.x / textureSize.x, m_size.y / textureSize.y });
}

void Didax::Button::updateColor()
{
	sf::Color mask;
	if (m_isPressed)
		mask = m_clickedColorMask;
	else if (m_isHovered)
		mask = m_hoverColorMask;
	else
		mask = m_standardColorMask;
	m_sprite.setColor(m_color * mask);
}
