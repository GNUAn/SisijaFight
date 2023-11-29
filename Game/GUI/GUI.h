#pragma once
#include "../../Gamemodes/Gamemodes.h"
#include <string>

struct LobbyReturnCode {
	GameMode* gamemode;
	std::string playerPath;
	std::string worldPath;
	std::string serverAddress;
};

class Lobby {
	void show();
};