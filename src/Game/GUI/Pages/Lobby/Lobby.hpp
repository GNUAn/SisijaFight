#pragma once
#include "Game/GUI/GUI.hpp"

struct LobbyReturnCode {
	GameMode* gamemode;
	std::string playerPath;
	std::string worldPath;
	std::string serverAddress;
};

class Lobby : public GUIClass {
public:
	void draw(GUIEnvironment* env) override;
};

class GamemodeSelection : public GUIPage {
public:
	void draw(GUIEnvironment* env) override;
};

class WorldSelection : public GUIPage {
public:
	void draw(GUIEnvironment* env) override;
};

class ServerSelection : public GUIPage {
public:
	void draw(GUIEnvironment* env) override;
};