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
		auto canv = me->createWidget<Didax::Canvas>();
		canv->setTexture("warrior");
		canv->setPosition(150, 150);
		canv->setSize(100,100);
		canv->setColorInTime(sf::Color::Red, 5);
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
	for (int i = 0; i < 500; i++)
	{
		auto v =e.addEntity<Test>();
		v->getWidget<Didax::Canvas>()->setPositionInTime(sf::Vector2f{ 1500,800 }, (i + 200.0f) / 200.0f);
	}
	e.run();
}