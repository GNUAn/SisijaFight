#include "SGE/SGU-S.h"
#include "globals.h"
#include "Game/Audio/Backend.h"
#include <thread>
#include "Tools/GUITools.h"

SFSession* Session;
SGES* GEngine;
SGUI* GUIEngine;
dimension2du screenSize;

int main() {
	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = true;
	params.AntiAlias = 24;
	params.DriverType = EDT_OPENGL;
	params.WindowSize = dimension2d<u32>(1000, 900);
	params.Bits = 32;
	params.Doublebuffer = true;
	params.Stereobuffer = true;
	params.Stencilbuffer = true;
	params.DeviceType = EIDT_BEST;
	params.DriverMultithreaded = false;
	params.UsePerformanceTimer = true;
	params.WithAlphaChannel = true;
	params.LoggingLevel = ELL_DEBUG;
	IrrlichtDevice* device = createDeviceEx(params);

	device->setWindowCaption(L"SisijaFight");
	device->setResizable(true);
	device->maximizeWindow();

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	device->run(); // Used to update the screenSize

	screenSize = driver->getScreenSize();

	GEngine = new SGES(device);
	Session = new SFSession(device);
	GUIEngine = new SGUI(device);

	Session->init();

	gSoloud.init();

	Sound s;
	s.loadSound("test.ogg", true);
	s.play();
	s.setLooping(true);

	while (device->run()) {
		driver->beginScene(true, true, getNewColor());
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
}