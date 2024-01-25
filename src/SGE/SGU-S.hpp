/*This File contains the Class for SGU-S (SisijaGraphicsUnit-Subsystem)
* (C) 2023 Lucas Gola
*/
#pragma once
#include <irrlicht.h>
#include <functional>
#include <map>
#include <irrBullet.h>
#include "IMGUIWrapper.hpp"

using namespace irr;
using namespace gui;
using namespace video;
using namespace scene;

enum SGEvent {
	SGE_COLLISION, // TODO: add other events
};

struct SceneNodeAndRigidBody {
	ISceneNode* sceneNode;
	IRigidBody* rigidBody;
};

class SCamera{
public:
	SCamera(ISceneManager* smgr);
	~SCamera();
	void attachTo(IBoneSceneNode* parent);
	void updateRotationX(f32 rot);
private:
	ICameraSceneNode* _internal_camera;
	IBoneSceneNode* _parent;
	ISceneManager* _smgr;
};