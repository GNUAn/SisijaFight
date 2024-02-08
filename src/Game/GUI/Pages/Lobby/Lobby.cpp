#include "Lobby.hpp"
#include "globals.hpp"
#include "Game/GUI/helpers/helpers.hpp"
#include <irrlicht.h>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <pugixml.hpp>
#include <Irrlicht/CGUIMeshViewer.h>
#include "Game/Session.hpp"
#include "Game/Audio/Backend.hpp"

/// @brief Creates the lobby elements
/// @param dev the Irrlicht Device

void Lobby::draw(GUIEnvironment* env) {

	static Sound s;
	s.loadSound("data/audio/music/Menu.ogg", true);
	s.play();
	s.setLooping(true);

	//SetGUIThemeColor(ThemeColor::Blue);

	GUIPage* gamemodeSelection = new GamemodeSelection();
	gamemodeSelection->draw(env);
	GUIPage* serverSelection;
	GUIPage* worldSelection;

	/*
	static ITexture* worldPreviewImage;
	static IGUIImage* worldPreview;
	static IGUIStaticText* worldLabelAuthor, * worldMaxPlayerSupport;
	static WorldInGUI currentWorld;
	static std::unordered_map<int, WorldInGUI> world_and_id;

	static GameMode* gamemode;

	auto g = dev->getGUIEnvironment();

	IGUIFont* arial = g->getFont("data/fonts/Arial.xml");

	static IGUIButton* buttonStart = g->addButton(s_rect(90, 80, 10, 20), 0, -1, translate("START").c_str());
	GUIEngine->addObject(buttonStart, [&](const irr::SEvent::SGUIEvent& event)
		{
			if (event.EventType == EGET_BUTTON_CLICKED) {
				event.Caller->setText(L"COOL!");
				LobbyReturnCode r;
				r.worldPath = currentWorld.path;
				r.gamemode = gamemode;
				GUIEngine->clearAll();
				Session->startGame(r, false);
			}
		}
	);
	buttonStart->setOverrideFont(arial);
	buttonStart->setEnabled(false);
	buttonStart->setToolTipText(translate("Select a world first!").c_str());

	ITexture* logo = dev->getVideoDriver()->getTexture("data/images/Logo16x9.png");
	ITexture* assistantLogo = dev->getVideoDriver()->getTexture("data/images/Spring.png");

	dimension2d<u32> imageSize = logo->getOriginalSize();
	float aspectRatio = (float)imageSize.Width / (float)imageSize.Height;
	int newHeight = screenSize.Width / aspectRatio;
	IGUIImage* guiImage = g->addImage(recti(0, 0, screenSize.Width, newHeight), 0, -1, L"Logo", true);
	guiImage->setImage(logo);
	guiImage->setScaleImage(true);

	GUILine* l1 = new GUILine(g, 0, -1);
	GUILine* l2 = new GUILine(g, 0, -1);
	GUILine* l3 = new GUILine(g, 0, -1);
	GUILine* l4 = new GUILine(g, 0, -1);
	GUILine* l5 = new GUILine(g, 0, -1);
	l1->setLineStartEnd(position2di(p(screenSize.Width, 50), newHeight), position2di(p(screenSize.Width, 50), p(screenSize.Height, 100)));
	l2->setLineStartEnd(position2di(p(screenSize.Width, 75), newHeight), position2di(p(screenSize.Width, 75), p(screenSize.Height, 80)));
	l3->setLineStartEnd(position2di(0, p(screenSize.Height, 80)), position2di(p(screenSize.Width, 100), p(screenSize.Height, 80)));
	l4->setLineStartEnd(position2di(0, newHeight), position2di(p(screenSize.Width, 100), newHeight));
	l5->setLineStartEnd(position2di(p(screenSize.Width, 25), newHeight), position2di(p(screenSize.Width, 25), p(screenSize.Height, 100)));

	static IGUIMeshViewer* playerFrame = g->addMeshViewer(s_rect(75, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 1, 25, 80 - std::round(((float)newHeight / (float)screenSize.Height) * 100) + 1));
	playerFrame->setMesh(dev->getSceneManager()->getMesh("data/players/sisija/sisija.x"));

	static IGUIButton* assistantButton = g->addButton(s_rect(80, 80, 10, 20), 0, -1, translate("Assistant").c_str(), translate("AI-Assistant Drady based on ChatGPT").c_str());
	assistantButton->setImage(assistantLogo);
	assistantButton->setScaleImage(true);
	assistantButton->setUseAlphaChannel(true);
	assistantButton->setOverrideFont(arial);

	GUIEngine->addObject(assistantButton, [](const SEvent::SGUIEvent) {});

	worldPreview = g->addImage(s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 10, 25, 34));
	worldLabelAuthor = g->addStaticText(translate("Level by: -select-a-world-first-").c_str(), s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 45, 25, 5), true, true, 0, -1, false);
	worldMaxPlayerSupport = g->addStaticText(translate("Maximum number of supported Players: -select-a-world-first-").c_str(), s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 50, 25, 10), true, true, 0, -1, false);

	static IGUIComboBox* worldSelection = g->addComboBox(s_rect(50, std::round(((float)newHeight / (float)screenSize.Height) * 100) + 1, 25, 7));

	std::vector<WorldInGUI> worlds = getWorlds(WORLD_INDEX_PATH_DATA);

	int counter = 0;
	for (WorldInGUI& w : worlds) {
		worldSelection->addItem(stringToWString(w.name).c_str());
		world_and_id[counter] = w;
		counter++;
	}

	GUIEngine->addObject(worldSelection,
		[&](const irr::SEvent::SGUIEvent& event)
		{
			if (event.EventType == EGET_COMBO_BOX_CHANGED) {
				IGUIComboBox* e = (IGUIComboBox*)event.Caller;
				currentWorld = world_and_id[e->getSelected()];
				worldPreviewImage = device->getVideoDriver()->getTexture(("data/worlds/" + currentWorld.icon).c_str());
				worldPreview->setImage(worldPreviewImage);
				worldPreview->setScaleImage(true);
				pugi::xml_document worldData;
				auto r = worldData.load_file(currentWorld.path.c_str());
				if (!r) { exit(5); }
				std::string author = worldData.child("world").attribute("author").as_string();
				std::string maxPlayers = worldData.child("world").attribute("maxPlayers").as_string();
				worldLabelAuthor->setText(stringToWString((translator::translate("Level by: ") + author)).c_str());
				worldMaxPlayerSupport->setText(stringToWString((translator::translate("Maximum number of Players: ") + maxPlayers)).c_str());
				buttonStart->setEnabled(true);
				buttonStart->setToolTipText(translate("Start Game").c_str());
			}
		}
	);

	static std::array<IGUICheckBox*, 3> gamemodeSelection;
	for (int i = 0; i < 3; i++) {
		gamemodeSelection[i] = g->addCheckBox(false, s_rect(1, std::round(((float)newHeight / (float)screenSize.Heigh^^t) * 100) + 1 + i * 6, 25, 6));
		GUIEngine->addObject(gamemodeSelection[i], [&, i](const SEvent::SGUIEvent& event)
			{
				if (event.EventType == EGET_CHECKBOX_CHANGED) {
					switch (i) {
					case 0:
						gamemode = new ClassicFight();
						break;
					}
					for (int li = 0; li < 3; li++) {
						if (li != i) {
							gamemodeSelection[li]->setChecked(false);
						}
					}
				}
			}
		);
	}
	gamemodeSelection[0]->setText(translate("Classic Fight").c_str());
	gamemodeSelection[1]->setText(translate("Tactic Fight").c_str());
	gamemodeSelection[2]->setText(translate("Story Mode").c_str());
	*/
}