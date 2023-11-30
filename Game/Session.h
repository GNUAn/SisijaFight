#pragma once
#include <irrlicht.h>
#include "GUI/GUI.h"
#include "../Gamemodes/Gamemodes.h"

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
	void startGame(LobbyReturnCode& c);
	GameMode* gamemode();
	Lobby* lobby();
	void init();
private:
	void setEventReceiver(S_EVR_CODE s);
	GameMode* _gamemode;
	Network* _network;
	Lobby* _lobby;
	World* _world;
	Player* _mainplayer;
	IEventReceiver* _evr;
};