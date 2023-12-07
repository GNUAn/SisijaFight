#pragma once
#include "../../Gamemodes/Gamemodes.h"
#include "Elements/MeshViewer.h"
#include "Elements/SuperTable.h"
#include <string>

struct LobbyReturnCode {
	GameMode* gamemode;
	std::string playerPath;
	std::string worldPath;
	std::string serverAddress;
};

class GUIPage {
public:
	void draw(IrrlichtDevice* dev);
	bool isFinished();
};
class GUIClass {
public:
	void draw(IrrlichtDevice* dev);
};

class Lobby : public GUIClass {
public:
	void draw(IrrlichtDevice* dev);
private:

};