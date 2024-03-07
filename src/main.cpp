#include "SGE/SGU-S.hpp"
#include "globals.hpp"
#include "Game/Audio/Backend.hpp"
#include "Tools/Translation/Translator.hpp"
#include "Game/Session.hpp"
#include "Network/NetworkManager.hpp"
#include <queue>
#include "Game/GUI/Widgets.hpp"
#include <functional>
#include "SGE/GUIEnvironment.hpp"

SFSession* Session;
GUIEnvironment* guienv;
dimension2du screenSize;
irr::IrrlichtDevice* device;

std::queue<std::function<void()>> funcQueue;

template<typename Func, typename... Args>
void addQueue(Func&& func, Args&&... args) {
    auto boundFunc = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
    funcQueue.push([=]() { boundFunc(); });
}

void workQueue(int numberOfTasks) {
    for (int i = 0; i < numberOfTasks; ++i) {
        if (!funcQueue.empty()) {
            std::function<void()> task = funcQueue.front();
            funcQueue.pop();
            task();
        } else {
            break;
        }
    }
}

/**
 * @mainpage SisijaFight 0.1.0
 *
 * SisijaFight is an open-source virtual paintball shooter with animal characters.
 *
 */

int main() {
	initNetworkManager();
	gSoloud.init();
	translator::initTranslator();

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
	params.Fullscreen = true;
	params.DriverMultithreaded = false;
	params.WithAlphaChannel = true;
	params.LoggingLevel = ELL_DEBUG;
	device = createDeviceEx(params);

	device->setWindowCaption(L"SisijaFight");
	device->setResizable(true);
	device->maximizeWindow();

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	guienv = new GUIEnvironment(device);

	device->run(); // Used to update the screenSize

	screenSize = driver->getScreenSize();

	Session = new SFSession(device);
	addQueue(&SFSession::init, Session);

	//checkProcessor();
	
	while (device->run()) {
		driver->beginScene(true, true, SColor(255, 0, 0, 0));
		workQueue(2);
		//Session->loopRoutine();
		guienv->drawAll();
		smgr->drawAll();
		driver->endScene();
	}
}