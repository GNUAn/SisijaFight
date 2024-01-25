#pragma once
#include "Configurator.hpp"
#include "compileConfig.h"
#include <irrlicht.h>

#define WORLD_INDEX_PATH_DATA "data/worlds/index.xml"

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

#define STD_RED SColor(255, 255, 0, 0)
#define STD_GREEN SColor(255, 255, 0, 0)
#define STD_BLUE SColor(255, 0, 0, 255)
#define STD_YELLOW SColor(255, 255, 255, 0)
#define STD_MAGENTA SColor(255, 255, 0, 255)
#define STD_CYAN SColor(255, 0, 255, 255)

class SFSession;
class SGES;
class SGUI;
class GUIEnvironment;

extern SFSession* Session;
extern irr::IrrlichtDevice* device;
extern GUIEnvironment* guienv;
extern irr::core::dimension2du screenSize;