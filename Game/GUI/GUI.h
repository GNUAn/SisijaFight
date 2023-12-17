#pragma once
#include "../../Gamemodes/Gamemodes.h"
#include "Elements/MeshViewer.h"
#include "Elements/SuperTable.h"
#include <string>
#include <irrlicht.h>

using namespace irr;

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
	 void onFinish(std::function<void()> f);
private:
	std::function<void()> end;
	bool finished;
	void finish();
};
class GUIClass {
public:
	 void draw(IrrlichtDevice* dev);
};

class Lobby : public GUIClass {
public:
	void draw(IrrlichtDevice* dev) ;
};