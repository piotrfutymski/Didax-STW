#include "Didax-Engine/Engine.h"

class Test
{
public:

	void setMe(Didax::Entity_ptr m)
	{
		me = m;
	}
	
	void onStart(Didax::Engine* e)
	{
		auto w = me->createWidget("testWIDG");
		//w->setPositionInTime(100, 100, 5);
	}

	void onUpdate(Didax::Engine* e)
	{
		//me->getWidget<Didax::Canvas>()->setSize(100, 100);
	}

	Didax::Entity_ptr me;


};


int main()
{
	Didax::Engine e("data/settings.json");
	e.setOwnCursor("arrowCUR", "handCUR", "loadingCUR");
	e.addEntity<Test>();
	e.run();
}