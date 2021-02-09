#include "TextArea.h"

Didax::TextArea::TextArea(AssetManager* a, Entity* e) :Widget(a, e)
{
	m_background.setFillColor(m_backgroundColor);
	m_font = nullptr;
}

sf::Color Didax::TextArea::getBackgroundColor() const
{
	return m_backgroundColor;
}

void Didax::TextArea::setBackgroundColor(sf::Color c)
{
	m_backgroundColor = c;
	m_background.setFillColor(c * m_color);
}

void Didax::TextArea::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	setBackgroundColor(sf::Color(r, g, b, a));
}

void Didax::TextArea::setFontColor(sf::Color c)
{
	m_fontColor = c;
	this->recalculateColor();
}

void Didax::TextArea::setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	setFontColor(sf::Color(r, g, b, a));
}

sf::String Didax::TextArea::getText() const
{
	return m_allText;
}

void Didax::TextArea::setText(const sf::String& s)
{
	m_allText = s;
	recalculateLines();
}

void Didax::TextArea::setFont(const std::string& name)
{
	auto t = m_assets->getAsset<FontAsset>(name);
	if (t == nullptr)
	{
		Logger::log("Font with name '" + name + "' is not loaded");
		return;
	}
	m_font = &(t->font);
	recalculateLines();
}

int Didax::TextArea::getCharacterSize() const
{
	return m_characterSize;
}

void Didax::TextArea::setCharacterSize(int s)
{
	m_characterSize = s;
	recalculateLines();
}

int Didax::TextArea::getLineSpacing() const
{
	return m_lineSpacing;
}

void Didax::TextArea::setLineSpacing(int s)
{
	m_lineSpacing = s;
	recalculateLinesPositions();
}

sf::Vector2f Didax::TextArea::getMargin() const
{
	return m_margin;
}

void Didax::TextArea::setMargin(const sf::Vector2f& m)
{
	m_margin = m;
	recalculateLines();
}

Didax::TextArea::Alaign Didax::TextArea::getAlaign() const
{
	return m_alaign;
}

void Didax::TextArea::setAlaign(Alaign a)
{
	m_alaign = a;
	recalculateLinesPositions();
}

void Didax::TextArea::resizeToText()
{
	setSize(getTextSize());
}

sf::Vector2f Didax::TextArea::getTextSize() const
{
	sf::Vector2f res{ 0,0 };
	for (int i = 0; i < m_textLines.size(); i++)
	{
		if (m_textLines[i].getGlobalBounds().width > res.x)
			res.x = m_textLines[i].getGlobalBounds().width;
	}
	res.y = m_margin.y + m_textLines.size() * (m_characterSize + m_lineSpacing);
	return res;
}

void Didax::TextArea::_update(float deltaT)
{
}

void Didax::TextArea::_input(const sf::Event& event)
{
}

void Didax::TextArea::_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_background);
	for (auto x : m_textLines)
	{
		target.draw(x);
	}
}

void Didax::TextArea::updatePosition()
{
	m_background.setPosition(m_absolute_position);
	this->recalculateLinesPositions();
}

void Didax::TextArea::updateSize()
{
	m_background.setSize(m_size);
	limitSize();
}

void Didax::TextArea::updateColor()
{
	setBackgroundColor(m_backgroundColor);
	setFontColor(m_fontColor);
}

void Didax::TextArea::recalculateLinesPositions()
{
	float x, y = 0;
	auto abs = m_absolute_position;
	for (size_t i = 0; i < m_textLines.size(); i++)
	{
		if (m_alaign == Alaign::Left)
		{
			x = m_margin.x;
		}
		else if (m_alaign == Alaign::Center)
		{
			float l = getTextLineLength(m_textLines[i]);
			x = (m_size.x - l) / 2;
		}
		else
		{
			float l = getTextLineLength(m_textLines[i]);
			x = (m_size.x - l - m_margin.x);
		}
		y = m_margin.y + i * (m_characterSize + m_lineSpacing);
		
		m_textLines[i].setPosition((int)(abs.x + x), (int)(abs.y + y));
	}
	m_background.setPosition(abs);
}

void Didax::TextArea::recalculateLines()
{
	m_textLines.clear();

	std::wstring buf = L"";
	std::vector<std::wstring> lines = {};
	std::wstringstream ss{ m_allText.toWideString() };
	
	while (std::getline(ss, buf))
		lines.push_back(buf);
	for (auto& l : lines)
	{
		ss = std::wstringstream{ l };
		sf::Text newLine;
		newLine.setFont(*m_font);
		newLine.setCharacterSize(m_characterSize);
		while (std::getline(ss, buf, L' '))
		{
			sf::String old = newLine.getString();
			newLine.setString(old + buf + L' ');
			if (getTextLineLength(newLine) > m_size.x - m_margin.x*2)
			{
				newLine.setString(old);
				m_textLines.push_back(newLine);
				newLine.setString(buf + L' ');
			}
		}
		m_textLines.push_back(newLine);
	}
	recalculateLinesPositions();
	recalculateColor();
}


void Didax::TextArea::recalculateColor()
{
	for (auto& x : m_textLines)
	{
		x.setFillColor(m_fontColor * m_color);
	}
}

float Didax::TextArea::getTextLineLength(const sf::Text& t)
{
	return t.getLocalBounds().width;
}
