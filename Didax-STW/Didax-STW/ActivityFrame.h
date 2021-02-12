#pragma once
#include "RootFrame.h"
#include "DragAndDrop.h"
#include "Game.h"
class ActivityFrame :
	public RootFrame
{

public:

	// Odziedziczono za poœrednictwem elementu RootFrame
	virtual void _onUpdate(Didax::Engine* e) override;
	virtual void _onStart(Didax::Engine* e) override;
	virtual void _onKill(Didax::Engine* e) override;
	virtual void _onCallback(const FrameEvent& e, Didax::Engine* eng) override;

private:

	Game* m_game;
	Activity* m_activity;
	Activity::State m_activityState;

	void beginTurn(Didax::Engine* eng);
	void createDragAndDrop(Didax::Engine* e);
};

