#pragma once
#include "Widget.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>

namespace Didax
{


	class TextArea : public Widget
	{
	public:

		enum class Alaign {
			Left, Center, Right
		};

		//constructors

		TextArea(AssetManager * a);

		//properties

		sf::Color getBackgroundColor()const;

		void setBackgroundColor(sf::Color);
		void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

		void setFontColor(sf::Color);
		void setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

		sf::String getText()const;
		void setText(const sf::String& s);

		void setFont(const std::string& name);

		int getCharacterSize()const;
		void setCharacterSize(int s);

		int getLineSpacing()const;
		void setLineSpacing(int s);

		sf::Vector2f getMargin()const;
		void setMargin(const sf::Vector2f& m);

		Alaign getAlaign()const;
		void setAlaign(Alaign a);

		void resizeToText();
		sf::Vector2f getTextSize()const;

	private:
		sf::String m_allText{ "" };
		std::vector<sf::Text> m_textLines;
		sf::RectangleShape m_background;
		sf::Color m_fontColor{ 0,0,0,255 };
		sf::Color m_backgroundColor{ 0,0,0,0 };
		sf::Font* m_font;
		int m_characterSize{ 30 };
		int m_lineSpacing{ 5 };
		sf::Vector2f m_margin{ 5,5 };
		Alaign m_alaign{ Alaign::Left };


		// Inherited via Widget
		virtual void _update(float deltaT) override;

		virtual void _input(const sf::Event& event) override;

		virtual void _draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual void updatePosition() override;

		virtual void updateSize() override;

		virtual void updateColor() override;
		//help functions

		void recalculateLinesPositions();
		void recalculateLines();

		void recalculateColor();

		float getTextLineLength(const sf::Text& t);



	};

}

