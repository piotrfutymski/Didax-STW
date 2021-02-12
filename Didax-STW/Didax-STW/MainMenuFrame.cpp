#include "MainMenuFrame.h"
#include "ActivityFrame.h"

void MainMenuFrame::_onUpdate(Didax::Engine* e)
{
}

void MainMenuFrame::_onStart(Didax::Engine* e)
{
}

void MainMenuFrame::_onKill(Didax::Engine* e)
{
}

void MainMenuFrame::_onCallback(const FrameEvent& e, Didax::Engine* eng)
{
	if (e.name == "game")
	{
		m_me->kill();
		eng->addEntity<ActivityFrame>("activityWIDG");
	}
	else if (e.name == "quit")
		eng->close();
}
