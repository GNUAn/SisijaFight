#include "Gamemodes.hpp"

#include <extensions/IProgressbar.h>
#include "../Game/GUI/GUI.hpp"

using namespace translator;

void ClassicFight::createInGameGUI(IGUIEnvironment* e) {
	IGUIWindow* playerProperties = e->addWindow(recti(10,10,300,180), false, stringToWString(translate("Player properties")).c_str());
	playerProperties->setDrawBackground(true);

	int scale = 18;
	recti windowSize = playerProperties->getAbsoluteClippingRect();
	int y = scale;
	for (uint8_t i = 0; i < 10; i++) {
		GUILine* line = new GUILine(e, playerProperties, -1);
		line->setLineStartEnd(position2di(0, y), position2di(windowSize.getWidth(), y));
		y += scale;
	}
}

void ClassicFight::startGame(World* world, Player* mainPlayer, IrrlichtDevice* dev) {
	_device = dev;
	_player = mainPlayer;
	_world = world;
	createInGameGUI(dev->getGUIEnvironment());
}

void ClassicFight::handleNetwork(nlohmann::json input) {

}

