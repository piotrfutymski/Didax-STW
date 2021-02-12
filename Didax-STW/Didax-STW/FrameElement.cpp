#include "FrameElement.h"
#include "RootFrame.h"

FrameElement::FrameElement(RootFrame* parent)
{
	m_parent = parent;
	m_callbackList[Didax::Widget::CallbackType::onHoverIn] = {};
	m_callbackList[Didax::Widget::CallbackType::onHoverOut] = {};
	m_callbackList[Didax::Widget::CallbackType::onPress] = {};
	m_callbackList[Didax::Widget::CallbackType::onRelease] = {};
	m_callbackList[Didax::Widget::CallbackType::onPressRight] = {};
}

void FrameElement::setMe(Didax::Entity_ptr m)
{
	m_me = m;
	auto w = m_me->getWidget();
	if (w == nullptr)
		w = m_me->createWidget < Didax::Button >();
	w->setWidgetEvent(Didax::Widget::CallbackType::onHoverIn, [this](Didax::Widget* w) {
		this->onHoverIn();
	});
	w->setWidgetEvent(Didax::Widget::CallbackType::onHoverOut, [this](Didax::Widget* w) {
		this->onHoverOut();
	});
	w->setWidgetEvent(Didax::Widget::CallbackType::onPress, [this](Didax::Widget* w) {
		this->onClick();
	});
	w->setWidgetEvent(Didax::Widget::CallbackType::onRelease, [this](Didax::Widget* w) {
		this->onRelease();
	});
	w->setWidgetEvent(Didax::Widget::CallbackType::onPressRight, [this](Didax::Widget* w) {
		this->onRightClick();
	});
}

void FrameElement::onClick()
{
	for (auto& c : m_callbackList[Didax::Widget::CallbackType::onPress])
	{
		m_parent->addCallback(c);
	}
}

void FrameElement::onRelease()
{
	for (auto& c : m_callbackList[Didax::Widget::CallbackType::onRelease])
	{
		m_parent->addCallback(c);
	}
}

void FrameElement::onHoverIn()
{
	for (auto& c : m_callbackList[Didax::Widget::CallbackType::onHoverIn])
	{
		m_parent->addCallback(c);
	}
}

void FrameElement::onHoverOut()
{
	for (auto& c : m_callbackList[Didax::Widget::CallbackType::onHoverOut])
	{
		m_parent->addCallback(c);
	}
}

void FrameElement::onRightClick()
{
	for (auto& c : m_callbackList[Didax::Widget::CallbackType::onPressRight])
	{
		m_parent->addCallback(c);
	}
}

void FrameElement::addCallback(const Didax::Widget::CallbackType& t, const FrameEvent& evnt)
{
	auto e = evnt;
	e.caller = m_me;
	m_callbackList[t].emplace_back(e);

}

std::vector<FrameEvent>& FrameElement::getCallbacks(const Didax::Widget::CallbackType& t)
{
	return m_callbackList[t];
}
