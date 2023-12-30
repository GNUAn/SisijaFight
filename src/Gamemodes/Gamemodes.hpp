#pragma once
#include <json.hpp>
#include "../Game/Player/Player.hpp"
#include "../Game/World/World.hpp"
#include "../SGE/SGU-S.hpp"

class GameMode {
public:
	virtual void startGame(World* world, Player* mainPlayer)=0;
	virtual void handleNetwork(nlohmann::json input)=0;
	virtual void createGUI(IGUIEnvironment* env)=0;
	virtual void createInGameGUI(IGUIEnvironment* env) = 0;
	virtual bool hasGUI()=0;
};

class ClassicFight : public GameMode{
	void startGame(World* world, Player* mainPlayer) override;
	void handleNetwork(nlohmann::json input) override;
	void createInGameGUI(IGUIEnvironment* env);
	bool hasGUI() { return false; }
};