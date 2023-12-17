#pragma once
#include "Game/Session.h"
#include "SGE/SGU-S.h"

#define WORLD_INDEX_PATH_DATA "data/worlds/index.xml"

extern SFSession* Session;
extern SGES* GEngine;
extern SGUI* GUIEngine;
extern irr::IrrlichtDevice* device;
extern dimension2du screenSize;