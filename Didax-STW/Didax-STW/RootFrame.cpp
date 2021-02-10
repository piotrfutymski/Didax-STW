#include "RootFrame.h"

RootFrame::RootFrame()
{
}

void RootFrame::setMe(Didax::Entity_ptr m)
{
	m_me = m;
	m_name = m->getName();
}

Didax::Entity_ptr RootFrame::getMe()
{
	return m_me;
}

void RootFrame::onStart(Didax::Engine* e)
{
	m_canvas = static_cast<Didax::Canvas*>(m_me->createWidget(m_name));
	initMyObjects(e, m_name);
	addMyObjectEvents(e);
	_onStart(e);
}

void RootFrame::onUpdate(Didax::Engine* e)
{
	updateCallbacks(e);
	updateHiding();
	_onUpdate(e);
	m_callbacks.clear();
}

void RootFrame::onKill(Didax::Engine* e)
{
	killMyObjects(e, m_name);
	_onKill(e);
}

void RootFrame::addCallback(const FrameEvent& e)
{
	m_callbacks.push_back(e);
}


void RootFrame::initMyObjects(Didax::Engine* e, const std::string& name)
{
	auto& mData = e->getAssets()->getAsset<Didax::DataAsset>(name)->data;
	if (mData.contains("hidden") && mData["hidden"] && name != m_name)
	{
		m_objects[name]->getWidget()->setVisible(false);
		m_objects[name]->getWidget()->setActive(false);
	}
	if (mData.contains("children"))
	{
		for (const std::string& cName : mData["children"])
		{
			m_objects[cName] = e->getEntity(cName);
			m_objects[cName]->addScript<FrameElement>(this);
			initMyObjects(e, cName);
		}
	}
}

void RootFrame::killMyObjects(Didax::Engine* e, const std::string& name)
{
	for (auto& x : m_objects)
		x.second->kill();
}

void RootFrame::addMyObjectEvents(Didax::Engine* e)
{
	for (auto& x : m_objects)
	{
		auto& mData = e->getAssets()->getAsset<Didax::DataAsset>(x.first)->data;
		if (mData.contains("events"))
		{
			auto scr = x.second->getScript<FrameElement>();
			for (auto& [key, val] : mData["events"].items())
				scr->addCallback(Didax::Widget::callbackFromName(key), FrameEvent(val));
		}
	}
}

void RootFrame::updateCallbacks(Didax::Engine* e)
{
	for (auto& evnt : m_callbacks)
	{
		if (evnt.name == "open")
			eventOpen(evnt.value, e);
		else if (evnt.name == "hide")
			eventHide(evnt.value, e);
		else if (evnt.name == "show")
			eventShow(evnt.value, e);
		else if (evnt.name == "close")
			eventClose(evnt.value, e);
		else if (evnt.name == "exit")
			eventExit(e);
		_onCallback(evnt, e);
	}
}

void RootFrame::updateHiding()
{
	if (m_hiding.size() > 0)
	{
		for (auto it = m_hiding.begin(); it != m_hiding.end();)
		{
			if (!(*it)->getWidget()->isMovingInTime())
			{
				(*it)->getWidget()->setVisible(false);
				(*it)->getWidget()->setActive(false);
				it = m_hiding.erase(it);
			}
			else
				it++;
		}
	}
}

void RootFrame::eventOpen(const std::string& toopen, Didax::Engine* e)
{
	auto toopenWidg = m_objects[toopen]->getWidget();
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toopen)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	toopenWidg->setPosition(pos);
	toopenWidg->setVisible(true);
	toopenWidg->setActive(true);
}

void RootFrame::eventShow(const std::string& toshow, Didax::Engine* e)
{
	auto toopenWidg = m_objects[toshow]->getWidget();
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toshow)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	sf::Vector2f siz{ toopenData["rectangle"]["width"], toopenData["rectangle"]["height"] };
	sf::Vector2f startingPos{ pos.x, -siz.y };
	toopenWidg->setPosition(startingPos);
	toopenWidg->setVisible(true);
	toopenWidg->setActive(true);
}

void RootFrame::eventClose(const std::string& toclose, Didax::Engine* e)
{
	auto tocloseWidg = m_objects[toclose]->getWidget();
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toclose)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	sf::Vector2f endPos{ pos.x, 1080 };
	tocloseWidg->setPosition(endPos);
	tocloseWidg->setVisible(false);
	tocloseWidg->setActive(false);
}

void RootFrame::eventHide(const std::string& toHide, Didax::Engine* e)
{
	auto tocloseWidg = m_objects[toHide]->getWidget();
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toHide)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	sf::Vector2f endPos{ pos.x, 1080 };
	tocloseWidg->setPositionInTime(endPos, 0.25);
	m_hiding.push_back(m_objects[toHide]);
}

void RootFrame::eventExit(Didax::Engine* e)
{
	m_me->kill();
}