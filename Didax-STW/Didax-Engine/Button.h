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
		std::string getTexture();

		//properties

		void setHoverMask(const sf::Color& c);
		void setClickedMask(const sf::Color& c);
		void setStandardMask(const sf::Color& c);
		sf::Color getHoverMask()const;
		sf::Color getClickedMask()const;
		sf::Color getStandardMask()const;

	private:

		sf::Sprite m_sprite;

		sf::Color m_standardColorMask{ 210, 210, 210, 255 };
		sf::Color m_hoverColorMask{ 255, 255, 255, 255 };
		sf::Color m_clickedColorMask{255, 255, 255, 255 };

		bool m_textureSet{ false };
		std::string m_texture = "";

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

