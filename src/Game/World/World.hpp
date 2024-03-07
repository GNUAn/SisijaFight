#pragma once
#include <irrlicht.h>
#include <irrBullet.h>
#include <string>
#include "SGE/Scripting.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class World {
public:
	World(IrrlichtDevice* dev, std::string path);
	~World();
	inline irrBulletWorld* getPhysicsWorld() { return _physics; }
	inline ScripterSub* getScriptingEngine() {return scripting; }
	IAnimatedMeshSceneNode* getSceneNode();
	void loadEntities();
private:
	IAnimatedMeshSceneNode* _node;
	irrBulletWorld* _physics;
	ScripterSub* scripting;
};