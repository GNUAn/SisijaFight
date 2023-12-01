#include "GUI.h"
#include "../../Tools/GUITools.h"
#include "../../globals.h"
#include <irrlicht.h>

void Lobby::draw(IrrlichtDevice* dev) {
	auto g = dev->getGUIEnvironment();
	IGUIButton* buttonStart = g->addButton(s_rect(10, 10, 80, 80), 0, -1, L"START", L"get into lobby");
	GUIEngine->addObject(buttonStart, [](const irr::SEvent::SGUIEvent& event) {if (event.EventType == EGET_BUTTON_CLICKED) { event.Caller->setText(L"CLICKED!"); }});
}