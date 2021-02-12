#include "ActivityFrame.h"


void ActivityFrame::_onUpdate(Didax::Engine* e)
{
}

void ActivityFrame::_onStart(Didax::Engine* e)
{
	m_game = e->addEntity<Game>()->getScript<Game>();
	m_game->init(e->getAssets());
	m_game->start({});
	m_game->startActivity("testACTV");
	m_activity = m_game->getActivity();
	m_activityState = m_activity->getState();
	createDragAndDrop(e);
	beginTurn(e);
}

void ActivityFrame::_onKill(Didax::Engine* e)
{
}

void ActivityFrame::_onCallback(const FrameEvent& e, Didax::Engine* eng)
{
}

void ActivityFrame::beginTurn(Didax::Engine* eng)
{
	m_activity->nextTurn();
	auto dad = m_objects["ActionPanelWIDG"]->getScript<DragAndDrop>();
	dad->clear(eng);
	auto activt = m_activity->getOnHandActions();
	int i = 0;
	for (auto& a : activt)
	{
		auto& dat = eng->getAssets()->getAsset<Didax::DataAsset>(a)->data;
		auto item = eng->addEntity<FrameElement>("actItem"+std::to_string(i),this);
		auto c = item->getWidget< Didax::Button>();
		c->setTexture(dat["texture"]);
		dad->addItem(item, i);
		i++;
	}

}

void ActivityFrame::createDragAndDrop(Didax::Engine* e)
{
	auto& data = e->getAssets()->getAsset<Didax::DataAsset>("ActionPanelWIDG")->data;
	std::vector<sf::Vector2f> pos;
	float y = data["info"]["DragandDropPositionsY"];
	for (auto& x: data["info"]["DragandDropPositionsX"])
	{
		pos.push_back({ x,y });
	}
	data = e->getAssets()->getAsset<Didax::DataAsset>("TurnPanelWIDG")->data;
	auto absA = m_objects["ActionPanelWIDG"]->getWidget()->getAbsolutePosition();
	auto absB = m_objects["TurnPanelWIDG"]->getWidget()->getAbsolutePosition();
	y = data["info"]["DragandDropPositionsY"] + absB.y - absA.y;
	for (auto& x : data["info"]["DragandDropPositionsX"])
	{
		pos.push_back({ x+absB.x-absA.x,y });
	}
	m_objects["ActionPanelWIDG"]->addScript<DragAndDrop>(pos, sf::Vector2f{ 80, 80 });
}
