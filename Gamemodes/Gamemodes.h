#pragma once
#include <json.hpp>
#include "../Game/Player/Player.h"
#include "../Game/World/World.h"
#include "../SGE/SGU-S.h"

class GameMode {
public:
	void startGame(World* world, Player* mainPlayer);
	void handleNetwork(nlohmann::json input);
	void createGUI(SGUI* env);
};