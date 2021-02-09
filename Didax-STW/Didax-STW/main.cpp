#include "RootFrame.h"
#include "Game.h"
#include "DragAndDrop.h"

class TestFrame : public RootFrame
{
public:

	virtual void _onUpdate(Didax::Engine* e) override
	{
	}

	virtual void _onStart(Didax::Engine* e) override
	{
		auto& data = e->getAssets()->getAsset<Didax::DataAsset>("TestDragandDropWIDG")->data;
		std::vector<sf::Vector2f> pos;
		for (int i = 0; i < 12; i+=2)
		{
			pos.push_back(sf::Vector2f(data["info"]["positions"][i], data["info"]["positions"][i + 1]));
		}
		dragAndDrop = e->getEntity("TestDragandDropWIDG");
		dragAndDrop->addScript<DragAndDrop>(pos, sf::Vector2f{ 64, 64 });
		for (int i = 0; i < 6; i++)
		{
			items[i] = e->addEntity<Item>();
			auto c = items[i]->createWidget< Didax::Canvas>();
			c->setTexture(data["info"]["textures"][i]);
			dragAndDrop->getWidget()->addChild(c);
			dragAndDrop->getScript<DragAndDrop>()->addItem(items[i], i);
		}
	}

	virtual void _onKill(Didax::Engine* e) override
	{
		e->close();
	}

private:
	
	Didax::Entity_ptr items[6];
	Didax::Entity_ptr dragAndDrop;

};


int main()
{
	Didax::Engine e("data/settings.json");
	e.setOwnCursor("arrowCUR", "handCUR", "loadingCUR");
	e.addEntity<TestFrame>("testWIDG");
	e.run();
}