#pragma once
#include <json.hpp>
#include "../Game/Player/Player.hpp"
#include "../Game/World/World.hpp"
#include "Network/NetworkHandler.hpp"
#include "../SGE/SGU-S.hpp"

class GameMode {
public:
	inline GameMode(IrrlichtDevice* dev, GUIEnvironment* env) :  _device(dev), _guienv(env) {
		_networkClient = new Network();
		_networkClient->addCallback([&, this](json in) { handleNetwork(in); });
	}
	virtual void startGame(World* world, Player* mainPlayer)=0;
	inline virtual void handleNetwork(json input) {
		if (input.contains("CLIENTID")) {
			int clientID = input["CLIENTID"].get<int>();
			// _player->setID(clientID);
		}
	}
	virtual void preloadAll();
	virtual void createGUI()=0;
	virtual void createInGameGUI() = 0;
	virtual void handle();
	inline virtual bool hasGUI() { return false; }
	virtual void end();
protected:
	IrrlichtDevice* _device;
	GUIEnvironment* _guienv;
	Player* _player;
	std::vector<Player*> _players;
	Network* _networkClient;
	World* _world;
};

class ClassicFight : public GameMode
{
	inline ClassicFight(IrrlichtDevice* dev, GUIEnvironment* env) : GameMode(dev, env) {}
	void startGame(World* world, Player* mainPlayer) override;
	void handleNetwork(nlohmann::json input) override;
	void createInGameGUI() override;
	inline bool hasGUI() override { return false; }
};