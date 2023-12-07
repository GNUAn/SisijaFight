#include "GUI.h"
#include "../../Tools/GUITools.h"
#include "../../globals.h"
#include "helpers/helpers.h"
#include <irrlicht.h>
#include <unordered_map>
#include <cmath>

void Lobby::draw(IrrlichtDevice* dev) {
	WorldInGUI currentWorld;

	auto g = dev->getGUIEnvironment();

	IGUIFont* arial = g->getFont("data/fonts/Arial.xml");

	IGUIButton* buttonStart = g->addButton(s_rect(90, 80, 10, 20), 0, -1, L"START", L"Start Game");
	GUIEngine->addObject(buttonStart, [](const irr::SEvent::SGUIEvent& event) {if (event.EventType == EGET_BUTTON_CLICKED) { event.Caller->setText(L"COOL!"); }});
	buttonStart->setOverrideFont(arial);

	GUILine* l1 = new GUILine(g, 0, -1);
	GUILine* l2 = new GUILine(g, 0, -1);
	l1->setLineStartEnd(position2di(p(screenSize.Width, 50), p(screenSize.Height, 0)), position2di(p(screenSize.Width, 50), p(screenSize.Height, 100)));
	l2->setLineStartEnd(position2di(p(screenSize.Width, 90), p(screenSize.Height, 0)), position2di(p(screenSize.Width, 90), p(screenSize.Height, 100)));

	InteractiveModelViewer* playerFrame = new InteractiveModelViewer(dev->getSceneManager());

	ITexture* logo = dev->getVideoDriver()->getTexture("data/images/Logo16x9.png");
	dimension2d<u32> imageSize = logo->getOriginalSize();
	float aspectRatio = (float)imageSize.Width / (float)imageSize.Height;
	int newHeight = screenSize.Width / aspectRatio;
	IGUIImage* guiImage = g->addImage(recti(0, 0, screenSize.Width, newHeight),0,-1,L"Logo",true);
	guiImage->setImage(logo);
	guiImage->setScaleImage(true);
	GUIEngine->addObject(guiImage, [](const SEvent::SGUIEvent) {});

	IGUIComboBox* worldSelection = g->addComboBox(s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100)+1, 40, 6));

	std::unordered_map<const wchar_t*, WorldInGUI> world_and_name;
	std::vector<WorldInGUI> worlds=getWorlds(WORLD_INDEX_PATH_DATA);

	for (WorldInGUI& w : worlds) {
		worldSelection->addItem(stringToWString(w.name).c_str());
		world_and_name[stringToWString(w.name).c_str()] = w;
	}

	GUIEngine->addObject(worldSelection, 
		[&](const irr::SEvent::SGUIEvent& event) 
			{
				if (event.EventType == EGET_COMBO_BOX_CHANGED) {
					IGUIComboBox* e = (IGUIComboBox*)event.Caller;
					currentWorld = world_and_name[e->getItem(e->getSelected())];
				}
			}
	);
}