#include "Gamemodes.hpp"

void GameMode::preloadAll() {
	//_world->getScriptingEngine()->registerClassMethod<World>("World", "void loadEntities()", &World::loadEntities);
}

void GameMode::end(){
	delete _player;
	delete _world;
	_networkClient->end();
	for (auto p : _players) {
		delete p;
	}
}
void GameMode::handle() {
	int current = _device->getTimer()->getTime();
	static int last = 0;
	_world->getPhysicsWorld()->stepSimulation((current - last) * 2);
	last = current;
}
