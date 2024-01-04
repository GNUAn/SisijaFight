#pragma once
#include <json.hpp>
#include "../Game/Player/Player.hpp"
#include "../Game/World/World.hpp"
#include "../SGE/SGU-S.hpp"

class GameMode {
public:
	virtual void startGame(World* world, Player* mainPlayer, IrrlichtDevice* dev)=0;
	virtual void handleNetwork(nlohmann::json input)=0;
	virtual void createGUI(IGUIEnvironment* env)=0;
	virtual void createInGameGUI(IGUIEnvironment* env) = 0;
	virtual bool hasGUI()=0;
protected:
	IrrlichtDevice* _device;
	Player* _player;
	World* _world;
};

class ClassicFight : public GameMode{
	void startGame(World* world, Player* mainPlayer, IrrlichtDevice* dev) override;
	void handleNetwork(nlohmann::json input) override;
	inline void createGUI(IGUIEnvironment* env) {};
	void createInGameGUI(IGUIEnvironment* env) override;
	inline bool hasGUI() { return false; }
};