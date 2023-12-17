/*This File contains the Class for SGU-S (SisijaGraphicsUnit-Subsystem)
* (C) 2023 Lucas Gola
*/
#pragma once
#include <irrlicht.h>
#include <functional>
#include <map>
#include <irrBullet.h>

using namespace irr;
using namespace gui;
using namespace video;
using namespace scene;

enum SGEvent {
	SGE_COLLISION, // TODO: add other events
};

class SGUI {
public:
	SGUI(IrrlichtDevice* dev);
	void handle(SEvent::SGUIEvent event);
	void addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback);
	void removeObject(IGUIElement* element);
	void clearAll();
private:
	IrrlichtDevice* _device;
	std::map<int, std::function<void(SEvent::SGUIEvent)>> _handler_and_object_id;
	int _current_id_counter=0;
};

class SGES {
public:
	SGES(IrrlichtDevice* dev);
	void addObject(IRigidBody* node, IRigidBody* body, std::function<void(SGEvent)> callback);
	void removeAllCallbacks();
private:
	std::map<int, std::function<void(SGEvent)>> _handler_and_object_id;
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