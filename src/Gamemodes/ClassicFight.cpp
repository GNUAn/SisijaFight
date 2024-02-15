#include "Gamemodes.hpp"

#include <extensions/IProgressbar.h>
#include "../Game/GUI/GUI.hpp"

using namespace translator;

void ClassicFight::createInGameGUI() {
	
}

void ClassicFight::startGame(World* world, Player* mainPlayer) {
	_player = mainPlayer;
	_world = world;
	createInGameGUI();
}

void ClassicFight::handleNetwork(nlohmann::json input) {

}

