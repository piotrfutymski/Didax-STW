#pragma once
#include "Didax-Engine/Engine.h"

class RootFrame
{
public:

	RootFrame();

	void setMe(Didax::Entity_ptr m);

	Didax::Entity_ptr getMe();
	
	void onStart(Didax::Engine* e);

	void onUpdate(Didax::Engine* e);

	void onKill(Didax::Engine* e);


protected:

	std::string m_name;
	Didax::Entity_ptr m_me{ nullptr };
	Didax::Canvas* m_canvas{ nullptr };

	std::unordered_map<std::string, Didax::Widget*> m_objects;
	std::vector< Didax::Widget*> m_closing;

protected:
	virtual void _onUpdate(Didax::Engine* e) = 0;
	virtual void _onStart(Didax::Engine* e) = 0;
	virtual void _onKill(Didax::Engine* e) = 0;

protected:

	void initMyObjects(Didax::Engine* e, const std::string & name);
	void killMyObjects(Didax::Engine* e, const std::string& name);
	void addMyObjectEvents(Didax::Engine* e);
	void addEventOpen(Didax::Widget* widg, const std::string& toopen, Didax::Widget::CallbackType type, Didax::Engine* e);
	void addEventHide(Didax::Widget* widg, const std::string& toclose, Didax::Widget::CallbackType type, Didax::Engine* e);
	void addEventExit(Didax::Widget* widg, Didax::Widget::CallbackType type);

};

