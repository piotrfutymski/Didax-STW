#include "RootFrame.h"

class TestFrame : public RootFrame
{
public:

	virtual void _onUpdate(Didax::Engine* e) override
	{
	}

	virtual void _onStart(Didax::Engine* e) override
	{
	}

	virtual void _onKill(Didax::Engine* e) override
	{
		e->close();
	}
};


int main()
{
	Didax::Engine e("data/settings.json");
	e.setOwnCursor("arrowCUR", "handCUR", "loadingCUR");
	e.addEntity<TestFrame>("testWIDG");
	e.run();
}