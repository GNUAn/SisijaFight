#include "GUI.h"
#include "../../Tools/GUITools.h"
#include "../../globals.h"
#include "helpers/helpers.h"
#include <irrlicht.h>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <pugixml.hpp>
#include <../../globals.h>

ITexture* worldPreviewImage;
IGUIImage* worldPreview;
IGUIStaticText* worldLabelAuthor, * worldMaxPlayerSupport;
WorldInGUI currentWorld;
std::unordered_map<int, WorldInGUI> world_and_id;

void Lobby::draw(IrrlichtDevice* dev) {
	auto g = dev->getGUIEnvironment();

	IGUIFont* arial = g->getFont("data/fonts/Arial.xml");

	IGUIButton* buttonStart = g->addButton(s_rect(90, 80, 10, 20), 0, -1, L"START", L"Start Game");
	GUIEngine->addObject(buttonStart, [](const irr::SEvent::SGUIEvent& event) {if (event.EventType == EGET_BUTTON_CLICKED) { event.Caller->setText(L"COOL!"); }});
	buttonStart->setOverrideFont(arial);

	GUILine* l1 = new GUILine(g, 0, -1);
	GUILine* l2 = new GUILine(g, 0, -1);
	GUILine* l3 = new GUILine(g, 0, -1);
	l1->setLineStartEnd(position2di(p(screenSize.Width, 50), p(screenSize.Height, 0)), position2di(p(screenSize.Width, 50), p(screenSize.Height, 100)));
	l2->setLineStartEnd(position2di(p(screenSize.Width, 75), p(screenSize.Height, 0)), position2di(p(screenSize.Width, 75), p(screenSize.Height, 80)));
	l3->setLineStartEnd(position2di(p(screenSize.Width, 0), p(screenSize.Height, 80)), position2di(p(screenSize.Width, 100), p(screenSize.Height, 80)));

	InteractiveModelViewer* playerFrame = new InteractiveModelViewer(dev->getSceneManager());

	ITexture* logo = dev->getVideoDriver()->getTexture("data/images/Logo16x9.png");
	dimension2d<u32> imageSize = logo->getOriginalSize();
	float aspectRatio = (float)imageSize.Width / (float)imageSize.Height;
	int newHeight = screenSize.Width / aspectRatio;
	IGUIImage* guiImage = g->addImage(recti(0, 0, screenSize.Width, newHeight),0,-1,L"Logo",true);
	guiImage->setImage(logo);
	guiImage->setScaleImage(true);
	GUIEngine->addObject(guiImage, [](const SEvent::SGUIEvent) {});

	worldPreview = g->addImage(s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 10, 25, 34));
	worldLabelAuthor = g->addStaticText(stringToWString("Level by: -select-a-world-first-").c_str(), s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 45, 25, 5), true, true, 0, -1, false);
	worldMaxPlayerSupport = g->addStaticText(stringToWString("Maximum number of supported Players: -select-a-world-first-").c_str(), s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 50, 25, 10), true, true, 0, -1, false);

	IGUIComboBox* worldSelection = g->addComboBox(s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100)+1, 25, 7));

	std::vector<WorldInGUI> worlds=getWorlds(WORLD_INDEX_PATH_DATA);

	int counter = 0;
	for (WorldInGUI& w : worlds) {
		worldSelection->addItem(stringToWString(w.name).c_str());
		world_and_id[counter] = w;
		counter++;
	}

	GUIEngine->addObject(worldSelection, 
		[](const irr::SEvent::SGUIEvent& event) 
			{
				if (event.EventType == EGET_COMBO_BOX_CHANGED) {
					IGUIComboBox* e = (IGUIComboBox*)event.Caller;
					currentWorld = world_and_id[e->getSelected()];
					worldPreviewImage = device->getVideoDriver()->getTexture(("data/worlds/"+currentWorld.icon).c_str());
					worldPreview->setImage(worldPreviewImage);
					worldPreview->setScaleImage(true);
					pugi::xml_document worldData;
					auto r = worldData.load_file(("data/worlds/" + currentWorld.path).c_str());
					if (!r) { exit(5); }
					std::string author = worldData.child("world").attribute("author").as_string();
					std::string maxPlayers = worldData.child("world").attribute("maxPlayers").as_string();
					worldLabelAuthor->setText(stringToWString(("Level by: " + author)).c_str());
					worldMaxPlayerSupport->setText(stringToWString(("Maximum number of Players: " + maxPlayers)).c_str());
				}
			}
	);
}