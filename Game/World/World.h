#pragma once
#include <irrlicht.h>
#include <irrbullet.h>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class World {
public:
	World(IrrlichtDevice* dev, std::string path);
	~World();
	irrBulletWorld* getPhysicsWorld();
	IAnimatedMeshSceneNode* getSceneNode();
	void loadEntities();
private:
	IAnimatedMeshSceneNode* _node;
	irrBulletWorld* _physics;
};