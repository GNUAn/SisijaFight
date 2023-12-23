#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

class SGUI;

class GUIEventReceiver : public IEventReceiver {
public:
	GUIEventReceiver(SGUI* env) : subsystem(env) {};

	virtual bool OnEvent(const SEvent& event);
private:
	SGUI* subsystem;
};