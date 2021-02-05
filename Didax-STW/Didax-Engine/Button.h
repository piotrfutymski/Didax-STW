#pragma once
#include "Widget.h"

namespace Didax
{

	class Entity;

	class Button : public Widget
	{
	public:

		Button(AssetManager* a, Entity*);

	public:

		void setTexture(const std::string& name);

		//properties

		void setHoverMask(const sf::Color& c);
		void setClickedMask(const sf::Color& c);
		sf::Color getHoverMask()const;
		sf::Color getClickedMask()const;

	private:

		sf::Sprite m_sprite;

		sf::Color m_hoverColorMask{ 200, 200, 200, 255 };
		sf::Color m_clickedColorMask{ 150, 150, 150, 255 };

		bool m_textureSet{ false };

	private:
		// Inherited via Widget
		virtual void _update(float deltaT) override;

		virtual void _input(const sf::Event& event) override;

		virtual void _draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual void updatePosition() override;

		virtual void updateSize() override;

		virtual void updateColor() override;

	};

}

