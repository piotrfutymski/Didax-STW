#pragma once
#include "RootFrame.h"
class MainMenuFrame :
	public RootFrame
{
	// Odziedziczono za po�rednictwem elementu RootFrame
	virtual void _onUpdate(Didax::Engine* e) override;
	virtual void _onStart(Didax::Engine* e) override;
	virtual void _onKill(Didax::Engine* e) override;
	virtual void _onCallback(const FrameEvent& e, Didax::Engine* eng) override;
};

