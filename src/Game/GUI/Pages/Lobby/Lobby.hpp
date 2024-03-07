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
	enum returnCodes { GMS_BAR_ONLINE=1, GMS_MODE_CLASSIC=2, GMS_MODE_TACTIC=4, GMS_MODE_ORDER=8, GMS_MODE_STORY=16 };
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