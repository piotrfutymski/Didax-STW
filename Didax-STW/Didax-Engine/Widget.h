#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <exception>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Input.h"

namespace Didax
{
	class Entity;

	class Widget : public sf::Drawable
	{
	public:

		enum class CallbackType {
			onHoverIn, onHoverOut, onPress, onRelease, onPressRight
		};

		using WidgetFunctionHolder_t = std::map<CallbackType, std::function<void(Widget*)>>;
		using CallbackHolder_t = std::vector<CallbackType>;

	public:

		Widget(AssetManager* a, Entity * e);

		void update(float dt);
		void input(const sf::Event& evt);

		bool isInArea(const sf::Vector2f& a, const sf::Vector2f& b);
		Entity* getEntity();

		void setPosition(const sf::Vector2f& pos);
		void setPosition(float x, float y);
		void move(const sf::Vector2f& deltaS);
		sf::Vector2f getPosition()const;

		void setAbsolutePosition(const sf::Vector2f& pos);
		void setAbsolutePosition(float x, float y);
		sf::Vector2f getAbsolutePosition()const;

		void setPositionInTime(const sf::Vector2f&, float T);
		void setPositionInTime(float x, float y, float T);

		void setColor(const sf::Color& c);
		void setColorInTime(const sf::Color& c, float T);
		sf::Color getColor()const;

		void setSize(const sf::Vector2f& s);
		void setSize(float x, float y);
		void resizeToChildren();
		sf::Vector2f getSizeWithChildren()const;
		sf::Vector2f getSize()const;

		Widget* getParent();
		const Widget* getParent()const;

		bool isHovered()const;
		bool isPressed()const;

		bool isInterable()const;
		void setInterable(bool i);

		bool isActive()const;
		void setActive(bool a);

		bool isVisible()const;
		void setVisible(bool v);

		bool isMovingInTime()const;

		const std::vector <Widget*>& getChildren()const;
		std::vector <Widget*>& getChildren();

		void setLimitArea(const sf::Vector2f& A, const sf::Vector2f& B);
		void setLimitArea(const sf::Rect<float>& f);
		void limitSize();
		void resetLimitArea();

		void setWidgetEvent(CallbackType t, const std::function<void(Widget*)>& func);
		void resetWidgetEvent(CallbackType t);

		bool isMouseIn()const;
		sf::Vector2f mouseRelativePos()const;

		bool addChild(Widget* child);
		void removeChild(Widget* child);

		static CallbackType callbackFromName(const std::string& n);

	protected:

		virtual void _update(float deltaT) = 0;
		virtual void _input(const sf::Event& event) = 0;
		virtual void _draw(sf::RenderTarget& target, sf::RenderStates states)const = 0;
		virtual void updatePosition() = 0;
		virtual void updateSize() = 0;
		virtual void updateColor() = 0;

		void setParent(Widget* parent);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:

		AssetManager* m_assets;
		WidgetFunctionHolder_t m_widgetEvent;
		CallbackHolder_t m_callbacks;

		sf::Vector2f m_position{ 0,0 };
		sf::Vector2f m_absolute_position{ 0,0 };
		sf::Vector2f m_size{ 0,0 };
		sf::Color m_color{ sf::Color::White };

		bool m_isHovered{ false };
		bool m_isPressed{ false };
		bool m_isInterable{ true };
		bool m_isVisible{ true };
		bool m_isActive{ true };

		std::vector<Widget*> m_children;
		Widget* m_parent{ nullptr };

		sf::Vector2f m_nextPos{ 0,0 };
		sf::Vector2f m_velocity{ 0,0 };
		float m_timeToMove{ 0 };
		bool m_movingInTime{ false };

		sf::Color m_nextColor{ sf::Color::White };
		sf::Color m_lastColor{ sf::Color::White };
		float m_timefromBeg{ 0 };
		float m_timeToChangeColor{ 0 };
		bool m_changingColor{ false };

		sf::Vector2f m_borderArea[2]{ {0,0},{0,0} };
		bool m_isSetArea{ false };

		Entity* m_entity_ptr;

	private:

		bool isPointInArea(const sf::Vector2f& point)const;
		void actualizeInTime(float deltaT);
		void actualizeMovingInTime(float deltaT);
		void actualizeColorInTime(float deltaT);
		void updateCallbacks();
		void poolEvents(const sf::Event& e);
		void updateEvents();

		void drawOnly(sf::RenderTarget& target, sf::RenderStates states) const;
		void recalculateAbsolutePosition(const sf::Vector2f& delta);
		void setPositionDontStop(const sf::Vector2f& pos);
		void moveDontStop(const sf::Vector2f& deltaS);
	};
}



