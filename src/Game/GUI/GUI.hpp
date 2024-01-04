#pragma once
#include <string>
#include <irrlicht.h>
#include "../../Tools/GUITools.hpp"
#include "../../Gamemodes/Gamemodes.hpp"
#include "Elements/SuperTable.hpp"

inline std::wstring translate(const std::string arg) {
	return stringToWString(translator::translate(arg));
}

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