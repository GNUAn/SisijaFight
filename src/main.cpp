#include "SGE/SGU-S.hpp"
#include "globals.hpp"
#include "Game/Audio/Backend.hpp"
#include "Tools/Translation/Translator.hpp"
#include "Game/Session.hpp"

SFSession* Session;
GUIEnvironment* guienv;
dimension2du screenSize;
irr::IrrlichtDevice* device;

/**
 * @mainpage SisijaFight 0.1.0
 *
 * SisijaFight is an open-source virtual paintball shooter with animal characters.
 *
 */

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
	params.Fullscreen = false;
	params.DriverMultithreaded = false;
	params.UsePerformanceTimer = true;
	params.WithAlphaChannel = true;
	params.LoggingLevel = ELL_DEBUG;
	device = createDeviceEx(params);

	device->setWindowCaption(L"SisijaFight");
	device->setResizable(true);
	device->maximizeWindow();

	gSoloud.init();

	guienv = new GUIEnvironment(device);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	translator::initTranslator();

	device->run(); // Used to update the screenSize

	screenSize = driver->getScreenSize();

	Session = new SFSession(device);

	Session->init();

	checkProcessor();

	while (device->run()) {
		driver->beginScene(true, true, SColor(255, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
}