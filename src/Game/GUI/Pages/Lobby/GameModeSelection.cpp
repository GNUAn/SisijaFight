#include "Lobby.hpp"

#define _(arg) translator::translate(arg)  

void GamemodeSelection::draw(GUIEnvironment* env) {
	GUISidebarMenu* modeSelect = new GUISidebarMenu(env, GUISidebarMenu::SGUI_SIDEBAR_UP, s_rect(15, 0, 70, 3), 2, { _("Online Multiplayer"), _("Local Singleplayer") });
	modeSelect->addCallback([](int e) { std::cout << e << std::endl; });
}
