#include "Lobby.hpp"
#include "Tools/Tools.hpp"

using namespace translator;

void GamemodeSelection::draw(GUIEnvironment* env) {
	/*
	GUIInvWindow* w = new GUIInvWindow(env, "", s_rect(0,0,100,100));
	GUISidebarMenu* modeSelect = new GUISidebarMenu(env, GUISidebarMenu::SGUI_SIDEBAR_UP, s_rect(15, 0, 70, 3), 2, { translate("Online Multiplayer"), translate("Local Singleplayer") });
	modeSelect->setParent(w);

	static int radioButtonValue, mode;
	static float difficultyValue;

	static GUIButton* next = new GUIButton(env, s_rect(15, 25, 70, 6), translate("Next"));
	next->setParent(w);

	GUIRadioButtonGroup* bg = new GUIRadioButtonGroup(env);
	GUIRadioButton* b = new GUIRadioButton(env, s_rect(18, 5, 100, 100), 0, translate("Classic Fight"));
	bg->addRadioButton(b);
	GUIRadioButton* b2 = new GUIRadioButton(env, s_rect(18, 10, 100, 100), 1, translate("Tactic Fight"));
	bg->addRadioButton(b2);
	GUIRadioButton* b3 = new GUIRadioButton(env, s_rect(18, 15, 100, 100), 2, translate("Story Mode"));
	bg->addRadioButton(b3); 
	GUIRadioButton* b4 = new GUIRadioButton(env, s_rect(18, 20, 100, 100), 3, translate("Orderkiller"));
	bg->addRadioButton(b4);
	bg->setParent(w);
	b->setParent(w);
	b2->setParent(w);
	b3->setParent(w);
	b4->setParent(w);

	GUITextLabel* lab = new GUITextLabel(env, s_rect(15, 36, 100, 100));
	lab->setText(translate("difficulty:"));
	lab->setParent(w);
	GUISlider* difficulty = new GUISlider(env, false, false, 1, 5, s_rect(15, 40, 70, 6));
	difficulty->addCallback([](float v) {});
	difficulty->setParent(w);

	bg->addCallback([](int c) { radioButtonValue=c; });

	modeSelect->addCallback([this](int e) {
		mode=e;
	});
	next->addCallback([this, &env](GUIEvent e) {
		long c=0;
		switch(radioButtonValue){
			case 0:
				c |= GMS_MODE_CLASSIC;
				break;
			case 1:
				c |= GMS_MODE_TACTIC;
				break;
			case 2:
				c |= GMS_MODE_STORY;
				break;
			case 3:
				c |= GMS_MODE_ORDER;
				break;
		}
		if(mode==0){
			c |= GMS_BAR_ONLINE;
		}
		c |= modulateFloatAt16Bit(difficultyValue);
		finish(c);
	});
	*/
	ImGui::PushFont(env->getFont("GUI_DEFAULT_FONT"));
	ImGui::SetNextWindowPos(i2imp(s_rect(0,0,70,100)));
	ImGui::SetNextWindowSize(i2im(s_rect(0,0,70,100)));
	ImGui::Begin("Main Menu");

	static int o_selection=1;
	ImGui::SetNextItemWidth(p(screenSize.Width,68));
	ImGui::SliderInt("##A", &o_selection, 1, 2, "");

	if(o_selection==1) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); }
	ImGui::Text(translate("Online Multiplayer").c_str());
	if(o_selection==1) { ImGui::PopStyleColor(); } else { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); }
	ImGui::SameLine();
	ImGui::SetCursorPosX(p(screenSize.Width,69)-ImGui::CalcTextSize(translate("Local Singleplayer").c_str()).x);
	ImGui::Text(translate("Local Singleplayer").c_str());
	if(o_selection==2){ ImGui::PopStyleColor(); }

	ImGui::Spacing();
	ImGui::SeparatorText(translate("Gamemode").c_str());
	static int gamemode=0;
	ImGui::RadioButton(translate("Classic Fight").c_str(), &gamemode, 1); ImGui::SameLine();
	ImGui::RadioButton(translate("Tactic Fight").c_str(), &gamemode, 2); ImGui::SameLine();
	ImGui::RadioButton(translate("Orderkiller").c_str(), &gamemode, 3); ImGui::SameLine();
	ImGui::RadioButton(translate("Storymode").c_str(), &gamemode, 4);
		
	ImGui::Spacing();
	ImGui::SeparatorText(translate("Difficulty").c_str());
	static float difficulty=0.5;
	ImGui::SetNextItemWidth(p(screenSize.Width,68));
	ImGui::PushFont(env->getFont("GUI_NUMBER_FONT"));
	ImGui::SliderFloat("##B", &difficulty, 0.5f, 10.0f);
	ImGui::PopFont();

	ImGui::Spacing();
	ImGui::Separator();
	if(ImGui::Button(translate("Next").c_str(), i2im(s_rect(0,0,70,5)))){
		long c=0;
		switch(gamemode){
			case 1:
				c |= GMS_MODE_CLASSIC;
				break;
			case 2:
				c |= GMS_MODE_TACTIC;
				break;
			case 3:
				c |= GMS_MODE_STORY;
				break;
			case 4:
				c |= GMS_MODE_ORDER;
				break;
		}
		if(o_selection==1){
			c |= GMS_BAR_ONLINE;
		}
		c |= modulateFloatAt16Bit(difficulty);
		finish(c);
	}

	ImGui::End();

	bool c=true;
	ImGui::SetNextWindowPos(i2imp(s_rect(70,0,30,100)));
	ImGui::SetNextWindowSize(i2im(s_rect(70,0,30,100)));
	ImGui::Begin("Player", &c);
	if(c==false){ exit(0); }
	
	ImGui::End();

	ImGui::PopFont();
}
