#pragma once
#include "Didax-Engine/Engine.h"
#include "FrameEvent.h"
#include "FrameElement.h"

class RootFrame
{
public:

	RootFrame();

	void setMe(Didax::Entity_ptr m);

	Didax::Entity_ptr getMe();
	
	void onStart(Didax::Engine* e);

	void onUpdate(Didax::Engine* e);

	void onKill(Didax::Engine* e);

	void addCallback(const FrameEvent& e);


protected:

	std::string m_name;
	Didax::Entity_ptr m_me{ nullptr };
	Didax::Canvas* m_canvas{ nullptr };
	
	std::vector<FrameEvent> m_callbacks{};

	std::unordered_map<std::string, Didax::Entity_ptr> m_objects;
	std::vector<Didax::Entity_ptr> m_hiding;

protected:
	virtual void _onUpdate(Didax::Engine* e) = 0;
	virtual void _onStart(Didax::Engine* e) = 0;
	virtual void _onKill(Didax::Engine* e) = 0;
	virtual void _onCallback(const FrameEvent& e, Didax::Engine* eng) = 0;

protected:

	void initMyObjects(Didax::Engine* e, const std::string & name);
	void killMyObjects(Didax::Engine* e, const std::string& name);

	void addMyObjectEvents(Didax::Engine* e);

	void updateCallbacks(Didax::Engine* e);
	void updateHiding();

	void eventOpen(const std::string & toopen, Didax::Engine* e);
	void eventShow(const std::string & toshow, Didax::Engine * e);
	void eventClose(const std::string& toclose, Didax::Engine* e);
	void eventHide(const std::string& toHide, Didax::Engine* e);
	void eventExit(Didax::Engine* e);
};

