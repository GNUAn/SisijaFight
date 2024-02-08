#include "Lobby.hpp"

using namespace translator;

void GamemodeSelection::draw(GUIEnvironment* env) {
	GUISidebarMenu* modeSelect = new GUISidebarMenu(env, GUISidebarMenu::SGUI_SIDEBAR_UP, s_rect(15, 0, 70, 3), 2, { translate("Online Multiplayer"), translate("Local Singleplayer") });
	
	static GUIButton* next = new GUIButton(env, s_rect(15, 25, 70, 6), translate("Next"));

	modeSelect->addCallback([](int e) {  });

	GUIRadioButtonGroup* bg = new GUIRadioButtonGroup(env);
	GUIRadioButton* b = new GUIRadioButton(env, s_rect(18, 5, 100, 100), 0, translate("Classic Fight"));
	bg->addRadioButton(b);
	GUIRadioButton* b2 = new GUIRadioButton(env, s_rect(18, 10, 100, 100), 1, translate("Tactic Fight"));
	bg->addRadioButton(b2);
	GUIRadioButton* b3 = new GUIRadioButton(env, s_rect(18, 15, 100, 100), 2, translate("Story Mode"));
	bg->addRadioButton(b3); 
	GUIRadioButton* b4 = new GUIRadioButton(env, s_rect(18, 20, 100, 100), 3, translate("Orderkiller"));
	bg->addRadioButton(b4);


	GUISlider* difficulty = new GUISlider(env, false, false, 1, 5, s_rect(15, 40, 70, 6));
	difficulty->addCallback([](float v) {});

	bg->addCallback([](int c) { });
}
