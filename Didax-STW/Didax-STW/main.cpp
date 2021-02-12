#include <thread>
#include "Game.h"
#include "DragAndDrop.h"
#include "MainMenuFrame.h"

int main()
{
	Didax::Engine e("data/settings.json");
	e.setOwnCursor("arrowCUR", "handCUR", "loadingCUR");
	e.addEntity<MainMenuFrame>("mainWIDG");
	e.run();
}