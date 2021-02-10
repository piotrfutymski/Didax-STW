#pragma once
#include "Didax-Engine/Engine.h"
#include "FrameEvent.h"

class RootFrame;

class FrameElement
{
public:

	FrameElement(RootFrame* parent);

	void setMe(Didax::Entity_ptr m);

	void onClick();
	void onRelease();
	void onHoverIn();
	void onHoverOut();
	void onRightClick();

	void addCallback(const Didax::Widget::CallbackType& t, const FrameEvent& evnt);
	//void removeCallback(const Didax::Widget::CallbackType& t, const FrameEvent& evnt);
	std::vector<FrameEvent>& getCallbacks(const Didax::Widget::CallbackType& t);

	//

private:

	Didax::Entity_ptr m_me;

	RootFrame* m_parent;

	std::unordered_map<Didax::Widget::CallbackType, std::vector<FrameEvent>> m_callbackList;

};

