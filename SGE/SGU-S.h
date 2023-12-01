/*This File contains the Class for SGU-S (SisijaGraphicsUnit-Subsystem)
* (C) 2023 Lucas Gola
*/
#pragma once
#include <irrlicht.h>
#include <functional>
#include <map>

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

class SGUI {
public:
	SGUI(IrrlichtDevice* dev);
	void handle(SEvent::SGUIEvent event);
	void addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback);
private:
	IrrlichtDevice* _device;
	std::map<int, std::function<void(SEvent::SGUIEvent)>> _handler_and_object_id;
	int _current_id_counter=0;
};
class SGES {
public:
	SGES(IrrlichtDevice* dev);
};