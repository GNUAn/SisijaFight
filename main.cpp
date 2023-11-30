#include "SGE/SGU-S.h"
#include "globals.h"
#include "Game/Audio/Backend.h"

SFSession* Session;
SGES* GEngine;

int main() {
	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = true;
	params.AntiAlias = 24;
	params.DriverType = EDT_OPENGL;
	params.WindowSize = dimension2d<u32>(800, 700);
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

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	GEngine = new SGES(device);
	Session = new SFSession();

	gSoloud.init();

	Sound s;
	s.loadSound("test.ogg", true);
	s.play();

	while (device->run()) {
		driver->beginScene(true, true, SColor(0, 255, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
		driver->drawStencilShadowVolume(true);
		driver->drawStencilShadow();
	}
}