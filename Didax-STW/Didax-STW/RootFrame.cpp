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
	if (m_closing.size() > 0)
	{
		for (auto it = m_closing.begin(); it != m_closing.end();)
		{
			if (!(*it)->isMovingInTime())
			{
				(*it)->setVisible(false);
				(*it)->setActive(false);
				it = m_closing.erase(it);
			}
			else
				it++;				
		}
	}
	
	_onUpdate(e);
}

void RootFrame::onKill(Didax::Engine* e)
{
	killMyObjects(e, m_name);
	_onKill(e);
}

void RootFrame::initMyObjects(Didax::Engine* e, const std::string& name)
{
	auto& mData = e->getAssets()->getAsset<Didax::DataAsset>(name)->data;
	if (mData.contains("hidden") && mData["hidden"])
	{
		m_objects[name]->setVisible(false);
		m_objects[name]->setActive(false);
	}
	if (mData.contains("children"))
	{
		for (const std::string& cName : mData["children"])
		{
			m_objects[cName] = e->getEntity(cName)->getWidget();
			initMyObjects(e, cName);
		}
	}
}

void RootFrame::killMyObjects(Didax::Engine* e, const std::string& name)
{
	auto& mData = e->getAssets()->getAsset<Didax::DataAsset>(name)->data;
	if (mData.contains("children"))
	{
		for (const std::string& cName : mData["children"])
		{		
			killMyObjects(e, cName);
			e->getEntity(cName)->kill();
		}
	}
}

void RootFrame::addMyObjectEvents(Didax::Engine* e)
{
	for (auto& obj: m_objects)
	{
		auto& objData = e->getAssets()->getAsset<Didax::DataAsset>(obj.first)->data;
		if (objData.contains("onPress"))
		{
			if (objData["onPress"].contains("open"))
				addEventOpen(obj.second, objData["onPress"]["open"], Didax::Widget::CallbackType::onPress,e);
			if(objData["onPress"].contains("hide"))
				addEventHide(obj.second, objData["onPress"]["hide"], Didax::Widget::CallbackType::onPress,e);
			if (objData["onPress"].contains("exit") && objData["onPress"]["exit"])
				addEventExit(obj.second, Didax::Widget::CallbackType::onPress);
		}
		if (objData.contains("onHoverIn"))
		{
			if (objData["onHoverIn"].contains("open"))
				addEventOpen(obj.second, objData["onHoverIn"]["open"], Didax::Widget::CallbackType::onHoverIn,e);
			if (objData["onHoverIn"].contains("hide"))
				addEventHide(obj.second, objData["onHoverIn"]["hide"], Didax::Widget::CallbackType::onHoverIn,e);
			if (objData["onHoverIn"].contains("exit") && objData["onHoverIn"]["exit"])
				addEventExit(obj.second, Didax::Widget::CallbackType::onHoverIn);
		}
		if (objData.contains("onHoverOut"))
		{
			if (objData["onHoverOut"].contains("open"))
				addEventOpen(obj.second, objData["onHoverOut"]["open"], Didax::Widget::CallbackType::onHoverOut,e);
			if (objData["onHoverOut"].contains("hide"))
				addEventHide(obj.second, objData["onHoverOut"]["hide"], Didax::Widget::CallbackType::onHoverOut,e);
			if (objData["onHoverOut"].contains("exit") && objData["onHoverOut"]["exit"])
				addEventExit(obj.second, Didax::Widget::CallbackType::onHoverOut);
		}
	}
}

void RootFrame::addEventOpen(Didax::Widget* widg, const std::string& toopen, Didax::Widget::CallbackType type, Didax::Engine* e)
{
	auto toopenWidg = m_objects[toopen];
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toopen)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	sf::Vector2f siz{ toopenData["rectangle"]["width"], toopenData["rectangle"]["height"] };
	sf::Vector2f startingPos{ pos.x, -siz.y };

	widg->setWidgetEvent(type, [toopenWidg, pos, startingPos](Didax::Widget*) {
		toopenWidg->setPosition(startingPos);
		toopenWidg->setPositionInTime(pos, 0.25);
		toopenWidg->setVisible(true);
		toopenWidg->setActive(true);
	});
}

void RootFrame::addEventHide(Didax::Widget* widg, const std::string& toclose, Didax::Widget::CallbackType type, Didax::Engine* e)
{
	auto tocloseWidg = m_objects[toclose];
	auto& toopenData = e->getAssets()->getAsset<Didax::DataAsset>(toclose)->data;
	sf::Vector2f pos{ toopenData["rectangle"]["x"], toopenData["rectangle"]["y"] };
	sf::Vector2f endPos{ pos.x, 1080 };
	auto clo = &this->m_closing;

	widg->setWidgetEvent(type, [tocloseWidg, endPos, clo](Didax::Widget*) {
		tocloseWidg->setPositionInTime(endPos, 0.25);
		clo->push_back(tocloseWidg);
	});
}


void RootFrame::addEventExit(Didax::Widget* widg, Didax::Widget::CallbackType type)
{
	widg->setWidgetEvent(type, [this](Didax::Widget*) {
		this->getMe()->kill();
	});
}
