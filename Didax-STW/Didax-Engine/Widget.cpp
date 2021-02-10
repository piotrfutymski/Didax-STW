#include "Widget.h"

Didax::Widget::Widget(AssetManager* a, Entity* e):m_assets(a), m_entity_ptr(e)
{
}

void Didax::Widget::update(float dt)
{
	if (!m_isActive)
		return;
	actualizeInTime(dt);
	if (m_isInterable)
	{
		updateEvents();
		updateCallbacks();
	}
	this->_update(dt);
	m_callbacks.clear();
}

void Didax::Widget::input(const sf::Event& evt)
{
	if (m_isInterable && m_isActive)
	{
		poolEvents(evt);
		this->_input(evt);
	}
}

bool Didax::Widget::isInArea(const sf::Vector2f& a, const sf::Vector2f& b)
{
	if (m_position.x > a.x && m_position.x + m_size.x< b.x && m_position.y > a.y && m_position.y + m_size.y < b.y)
		return true;
	return false;
}

Didax::Entity* Didax::Widget::getEntity()
{
	return m_entity_ptr;
}

void Didax::Widget::setPosition(const sf::Vector2f& pos)
{
	if (m_movingInTime)
		m_movingInTime = false;
	this->setPositionDontStop(pos);
}

void Didax::Widget::setPosition(float x, float y)
{
	setPosition({ x,y });
}

void Didax::Widget::move(const sf::Vector2f& deltaS)
{
	setPosition(deltaS.x + m_position.x, deltaS.y + m_position.y);
}

sf::Vector2f Didax::Widget::getPosition() const
{
	return m_position;
}

void Didax::Widget::setAbsolutePosition(const sf::Vector2f& pos)
{
	if (m_movingInTime)
		m_movingInTime = false;

	if (m_parent == nullptr)
		setPosition(pos);
	else
	{
		auto delta = pos - m_absolute_position;
		move(delta);
	}
}

void Didax::Widget::setAbsolutePosition(float x, float y)
{
	setAbsolutePosition({ x,y });
}

sf::Vector2f Didax::Widget::getAbsolutePosition() const
{
	return m_absolute_position;
}

void Didax::Widget::setPositionInTime(const sf::Vector2f& pos, float T)
{
	m_movingInTime = true;
	m_nextPos = pos;
	m_velocity = { (pos.x - m_position.x) / T, (pos.y - m_position.y) / T };
	m_timeToMove = T;
}

void Didax::Widget::setPositionInTime(float x, float y, float T)
{
	setPositionInTime({ x,y }, T);
}

void Didax::Widget::setColor(const sf::Color& c)
{
	m_color = c;
	this->updateColor();
}

void Didax::Widget::setColorInTime(const sf::Color& c, float T)
{
	m_changingColor = true;
	m_nextColor = { c.r, c.g,c.b,c.a };
	m_lastColor = m_color;
	m_timefromBeg = 0;
	m_timeToChangeColor = T;
}

sf::Color Didax::Widget::getColor() const
{
	return m_color;
}

void Didax::Widget::setSize(const sf::Vector2f& s)
{
	m_size = s;
	updateSize();
}

void Didax::Widget::setSize(float x, float y)
{
	setSize({ x,y });
}

void Didax::Widget::resizeToChildren()
{
	setSize(getSizeWithChildren());
}

sf::Vector2f Didax::Widget::getSizeWithChildren() const
{
	sf::Vector2f res{ 0,0 };
	if (m_children.size() == 0)
		res;
	for (auto x : m_children)
	{
		auto p = x->getPosition();
		auto s = x->getSize();
		if (p.x + s.x > res.x)
			res.x = p.x + s.x;
		if (p.y + s.y > res.y)
			res.y = p.y + s.y;
	}
	return res;
}

sf::Vector2f Didax::Widget::getSize() const
{
	return m_size;
}

Didax::Widget* Didax::Widget::getParent()
{
	return m_parent;
}

const Didax::Widget* Didax::Widget::getParent() const
{
	return m_parent;
}

bool Didax::Widget::isHovered() const
{
	return m_isHovered;
}

bool Didax::Widget::isPressed() const
{
	return m_isPressed;
}


bool Didax::Widget::isInterable() const
{
	return m_isInterable;
}

void Didax::Widget::setInterable(bool i)
{
	m_isInterable = i;
	m_isHovered = false;
	m_isPressed = false;
	m_callbacks.clear();
}

bool Didax::Widget::isActive() const
{
	return m_isActive;
}

void Didax::Widget::setActive(bool a)
{
	m_isActive = a;
	for (auto x : m_children)
		x->setActive(a);
}

bool Didax::Widget::isVisible() const
{
	return m_isVisible;
}

void Didax::Widget::setVisible(bool v)
{
	m_isVisible = v;
	for (auto x : m_children)
		x->setVisible(v);
}

bool Didax::Widget::isMovingInTime() const
{
	return m_movingInTime;
}

const std::vector<Didax::Widget*>& Didax::Widget::getChildren() const
{
	return m_children;
}

std::vector<Didax::Widget*>& Didax::Widget::getChildren()
{
	return m_children;
}

void Didax::Widget::setLimitArea(const sf::Vector2f& A, const sf::Vector2f& B)
{
	m_borderArea[0].x = A.x;
	m_borderArea[0].y = A.y;
	m_borderArea[1].x = B.x;
	m_borderArea[1].y = B.y;
	for (auto x : m_children)
		x->setLimitArea(A - x->getPosition(), B - x->getPosition());
	m_isSetArea = true;
}

void Didax::Widget::setLimitArea(const sf::Rect<float>& f)
{
	setLimitArea({ f.left, f.top }, { f.left + f.width, f.top + f.height });
}

void Didax::Widget::limitSize()
{
	this->setLimitArea({ 0,0, m_size.x, m_size.y });
}

void Didax::Widget::resetLimitArea()
{
	m_borderArea[0] = { 0,0 };
	m_borderArea[1] = { 0,0 };
	m_isSetArea = false;
	for (auto x : m_children)
		x->resetLimitArea();
}

void Didax::Widget::setWidgetEvent(CallbackType t, const std::function<void(Widget*)>& func)
{
	m_widgetEvent[t] = func;
}

void Didax::Widget::resetWidgetEvent(CallbackType t)
{
	m_widgetEvent.erase(t);
}

bool Didax::Widget::isMouseIn() const
{
	sf::Vector2f mousePos = (sf::Vector2f)Input::getMousePosition();
	return isPointInArea(mousePos);
}

sf::Vector2f Didax::Widget::mouseRelativePos() const
{
	auto minPos = m_absolute_position;
	auto mousePos = Input::getMousePosition();
	return { ((mousePos.x - minPos.x) / m_size.x), ((mousePos.y - minPos.y) / m_size.y) };
}

bool Didax::Widget::addChild(Widget* child)
{
	auto parent = this;
	while (parent != nullptr)
	{
		if (parent == child)
			return false;
		parent = parent->getParent();
	}
	if (child->getParent() != nullptr)
		return false;
	m_children.push_back(child);
	child->setParent(this);
	return true;
}

void Didax::Widget::removeChild(Widget* child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

Didax::Widget::CallbackType Didax::Widget::callbackFromName(const std::string& n)
{
	if (n == "onHoverIn")
		return CallbackType::onHoverIn;
	if (n == "onHoverOut")
		return CallbackType::onHoverOut;
	if (n == "onPress")
		return CallbackType::onPress;
	if (n == "onRelease")
		return CallbackType::onRelease;
	if (n == "onPressRight")
		return CallbackType::onPressRight;
	return CallbackType::onPress;
}

void Didax::Widget::setParent(Widget* parent)
{
	m_parent = parent;
	setPositionDontStop(m_position);
	setSize(m_size);
}

void Didax::Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_isVisible)
		return;

	if (m_isSetArea)
	{
		auto h_w = Input::getRezolution().y;
		auto pos = m_absolute_position;
		::glEnable(GL_SCISSOR_TEST);
		::glScissor(m_borderArea[0].x + pos.x, h_w - m_borderArea[1].y - pos.y, m_borderArea[1].x - m_borderArea[0].x, m_borderArea[1].y - m_borderArea[0].y);
		this->drawOnly(target, states);
		::glDisable(GL_SCISSOR_TEST);
	}
	else
		this->drawOnly(target, states);
}

bool Didax::Widget::isPointInArea(const sf::Vector2f& point)const
{
	auto minPos = m_absolute_position;
	auto maxPos = minPos + m_size;
	if (m_isSetArea)
	{
		if (minPos.x < m_borderArea[0].x)
			minPos.x = m_borderArea[0].x;
		if (minPos.y < m_borderArea[0].y)
			minPos.y = m_borderArea[0].y;
		if (maxPos.x > m_borderArea[1].x)
			maxPos.x = m_borderArea[1].x;
		if (maxPos.y > m_borderArea[1].y)
			maxPos.y = m_borderArea[1].y;
	}
	if (point.x > minPos.x && point.x < maxPos.x && point.y > minPos.y && point.y < maxPos.y)
		return true;
	return false;
}

void Didax::Widget::actualizeInTime(float deltaT)
{
	if (m_movingInTime)
		actualizeMovingInTime(deltaT);
	if (m_changingColor)
		actualizeColorInTime(deltaT);
}

void Didax::Widget::actualizeMovingInTime(float deltaT)
{
	moveDontStop({ (deltaT * m_velocity.x), (deltaT * m_velocity.y) });
	m_timeToMove -= deltaT;
	if (m_timeToMove <= 0)
	{
		m_movingInTime = false;
		m_timeToMove = 0;
		setPositionDontStop(m_nextPos);
	}
}

void Didax::Widget::actualizeColorInTime(float deltaT)
{
	m_timefromBeg += deltaT;
	sf::Color C;
	auto v = (m_timefromBeg / m_timeToChangeColor);
	C.r = v * m_nextColor.r + (1.0f-v)*m_lastColor.r;
	C.g = v * m_nextColor.g + (1.0f - v) * m_lastColor.g;
	C.b = v * m_nextColor.b + (1.0f - v) * m_lastColor.b;
	C.a = v * m_nextColor.a + (1.0f - v) * m_lastColor.a;
	this->setColor(C);
	if (m_timefromBeg > m_timeToChangeColor)
	{
		m_changingColor = false;
		this->setColor(m_nextColor);
	}
}

void Didax::Widget::updateCallbacks()
{
	for (auto it = m_callbacks.begin(); it != m_callbacks.end(); it++)
		if (m_widgetEvent.find(*it) != m_widgetEvent.end())
			m_widgetEvent[*it](this);
}

void Didax::Widget::poolEvents(const sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left && isMouseIn())
	{
		m_isPressed = true;
		m_callbacks.push_back(CallbackType::onPress);
	}
	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Right && isMouseIn())
		m_callbacks.push_back(CallbackType::onPressRight);

	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left && m_isPressed)
	{
		m_isPressed = false;
		m_callbacks.push_back(CallbackType::onRelease);
	}
		
}

void Didax::Widget::updateEvents()
{
	auto isMouseInn = isMouseIn();
	if (isMouseInn && m_isHovered == false)
	{
		m_isHovered = true;
		m_callbacks.push_back(CallbackType::onHoverIn);
	}
	else if (!isMouseInn && m_isHovered == true)
	{
		m_isHovered = false;
		m_callbacks.push_back(CallbackType::onHoverOut);
	}
	/*if (m_isPressed && !isMouseInn)
	{
		m_isPressed = false;
		m_callbacks.push_back(CallbackType::onRelease);
	}*/
}

void Didax::Widget::drawOnly(sf::RenderTarget& target, sf::RenderStates states) const
{
	this->_draw(target, states);
}

void Didax::Widget::recalculateAbsolutePosition(const sf::Vector2f& delta)
{

	if (m_parent == nullptr)
		m_absolute_position = m_position;
	else
		m_absolute_position = m_parent->getAbsolutePosition() + m_position;
}

void Didax::Widget::setPositionDontStop(const sf::Vector2f& pos)
{
	auto delta = pos - m_position;
	m_position = pos;
	recalculateAbsolutePosition(delta);
	updatePosition();
	for (auto x : m_children)
	{
		x->setPositionDontStop(x->getPosition());
	}
	
}

void Didax::Widget::moveDontStop(const sf::Vector2f& deltaS)
{
	setPositionDontStop({ deltaS.x + m_position.x, deltaS.y + m_position.y });
}
