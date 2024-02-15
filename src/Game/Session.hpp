#pragma once
#include <irrlicht.h>
#include "GUI/GUI.hpp"
#include "../Gamemodes/Gamemodes.hpp"
#include "Game/GUI/Pages/Lobby/Lobby.hpp"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;

extern bool game;

class Network;

enum S_EVR_CODE {
	S_EVR_GAME, S_EVR_LOBBY
};

class SFSession {
public:
	SFSession(IrrlichtDevice* dev) : _device(dev) {

	}
	void loopRoutine();
	void endGame();
	void startGame(LobbyReturnCode c, bool isGMGUIDone);
	GameMode* gamemode();
	Lobby* lobby();
	void init();
private:
	void setEventReceiver(S_EVR_CODE s);
	void startGameInternal(LobbyReturnCode c);
	GameMode* _gamemode;
	Lobby* _lobby;
	IEventReceiver* _evr;
	IrrlichtDevice* _device;
};

class GUISession {
public:
	inline void setCurrentGUIPage(GUIPage* p) {
		currentPage = p;
	}
	void resizeUI() {
		currentPage->draw(guienv);
	}
private:
	GUIPage* currentPage;
};
