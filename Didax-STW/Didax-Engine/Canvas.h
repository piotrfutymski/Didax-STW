#pragma once
#include "Widget.h"

namespace Didax
{
	class Entity;

	class Canvas : public Widget
	{
	public:

		enum class BackgroundType {
			None, Rect, Image
		};

		Canvas(AssetManager * a, Entity*);

		void setTexture(const std::string & name);

		std::string getTexture();

		void setRect();

		void unsetBackground();

	private:

		sf::RectangleShape m_backgroundRect;

		sf::Sprite m_backgroundSprite;
		std::string m_texture = "";

		BackgroundType m_bType{ BackgroundType::None };
		
		virtual void _update(float deltaT) override;
		virtual void _input(const sf::Event& event) override;
		virtual void _draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void updatePosition() override;
		virtual void updateSize() override;
		virtual void updateColor() override;
	};

}
