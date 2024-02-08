#include "IMGUIWrapper.hpp"

// Set themes

void SetGUIThemeColor(ThemeColor themeColor) {
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 colorForText, colorForHead, colorForArea, colorForBody, colorForPops;
	ImVec4 button, buttonHovered, buttonActive;

	switch (themeColor) {
	case ThemeColor::Red:
		colorForText = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colorForHead = ImVec4(0.70f, 0.20f, 0.20f, 1.00f);
		colorForArea = ImVec4(0.40f, 0.10f, 0.10f, 0.50f);
		colorForBody = ImVec4(0.15f, 0.05f, 0.05f, 1.00f);
		colorForPops = ImVec4(0.20f, 0.07f, 0.07f, 1.00f);
		button = ImVec4(0.75f, 0.25f, 0.25f, 1.00f);
		buttonHovered = ImVec4(0.85f, 0.30f, 0.30f, 1.00f);
		buttonActive = ImVec4(0.90f, 0.40f, 0.40f, 1.00f);
		break;

	case ThemeColor::Green:
		colorForText = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
		colorForHead = ImVec4(0.20f, 0.70f, 0.20f, 1.00f);
		colorForArea = ImVec4(0.10f, 0.40f, 0.10f, 0.50f);
		colorForBody = ImVec4(0.05f, 0.15f, 0.05f, 1.00f);
		colorForPops = ImVec4(0.07f, 0.20f, 0.07f, 1.00f);
		button = ImVec4(0.25f, 0.75f, 0.25f, 1.00f);
		buttonHovered = ImVec4(0.30f, 0.85f, 0.30f, 1.00f);
		buttonActive = ImVec4(0.40f, 0.90f, 0.40f, 1.00f);
		break;

	case ThemeColor::White:
		colorForText = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colorForHead = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
		colorForArea = ImVec4(0.60f, 0.60f, 0.60f, 0.50f);
		colorForBody = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colorForPops = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
		button = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
		buttonHovered = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
		buttonActive = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		break;
	case ThemeColor::Blue:
		colorForText = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colorForHead = ImVec4(0.20f, 0.20f, 0.70f, 1.00f);
		colorForArea = ImVec4(0.10f, 0.10f, 0.40f, 0.50f);
		colorForBody = ImVec4(0.05f, 0.05f, 0.15f, 1.00f);
		colorForPops = ImVec4(0.07f, 0.07f, 0.20f, 1.00f);
		button = ImVec4(0.25f, 0.25f, 0.75f, 1.00f);
		buttonHovered = ImVec4(0.30f, 0.30f, 0.85f, 1.00f);
		buttonActive = ImVec4(0.40f, 0.40f, 0.90f, 1.00f);
		break;
	case ThemeColor::Yellow:
		colorForText = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colorForHead = ImVec4(0.70f, 0.70f, 0.20f, 1.00f);
		colorForArea = ImVec4(0.40f, 0.40f, 0.10f, 0.50f);
		colorForBody = ImVec4(0.15f, 0.15f, 0.05f, 1.00f);
		colorForPops = ImVec4(0.20f, 0.20f, 0.07f, 1.00f);
		button = ImVec4(0.75f, 0.75f, 0.25f, 1.00f);
		buttonHovered = ImVec4(0.85f, 0.85f, 0.30f, 1.00f);
		buttonActive = ImVec4(0.90f, 0.90f, 0.40f, 1.00f);
		break;
	}

	// Grundlegende Farben
	style.Colors[ImGuiCol_Text] = colorForText;
	style.Colors[ImGuiCol_WindowBg] = colorForBody;
	style.Colors[ImGuiCol_ChildBg] = colorForArea;
	style.Colors[ImGuiCol_PopupBg] = colorForPops;
	style.Colors[ImGuiCol_Border] = colorForHead;
	style.Colors[ImGuiCol_FrameBg] = colorForArea;
	style.Colors[ImGuiCol_MenuBarBg] = colorForArea;
	style.Colors[ImGuiCol_ScrollbarBg] = colorForArea;
	style.Colors[ImGuiCol_CheckMark] = colorForText;
	style.Colors[ImGuiCol_SliderGrab] = colorForHead;
	style.Colors[ImGuiCol_SliderGrabActive] = colorForHead;
	style.Colors[ImGuiCol_ResizeGrip] = colorForHead;
	style.Colors[ImGuiCol_Tab] = colorForHead;
	style.Colors[ImGuiCol_TabUnfocused] = colorForArea;
	style.Colors[ImGuiCol_PlotLines] = colorForText;
	style.Colors[ImGuiCol_PlotHistogram] = colorForHead;

	// Buttons
	style.Colors[ImGuiCol_Button] = button;
	style.Colors[ImGuiCol_ButtonHovered] = buttonHovered;
	style.Colors[ImGuiCol_ButtonActive] = buttonActive;

	// Andere Zustände
	style.Colors[ImGuiCol_FrameBgHovered] = colorForHead;
	style.Colors[ImGuiCol_FrameBgActive] = colorForHead;
	style.Colors[ImGuiCol_TitleBg] = colorForHead;
	style.Colors[ImGuiCol_TitleBgActive] = colorForHead;
	style.Colors[ImGuiCol_TitleBgCollapsed] = colorForHead;
	style.Colors[ImGuiCol_ScrollbarGrab] = colorForHead;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = colorForHead;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = colorForHead;
	style.Colors[ImGuiCol_Header] = colorForHead;
	style.Colors[ImGuiCol_HeaderHovered] = colorForHead;
	style.Colors[ImGuiCol_HeaderActive] = colorForHead;
	style.Colors[ImGuiCol_Separator] = colorForHead;
	style.Colors[ImGuiCol_SeparatorHovered] = colorForHead;
	style.Colors[ImGuiCol_SeparatorActive] = colorForHead;
	style.Colors[ImGuiCol_ResizeGripHovered] = colorForHead;
	style.Colors[ImGuiCol_ResizeGripActive] = colorForHead;
	style.Colors[ImGuiCol_TabHovered] = colorForHead;
	style.Colors[ImGuiCol_TabActive] = colorForHead;
	style.Colors[ImGuiCol_TabUnfocusedActive] = colorForArea;
	style.Colors[ImGuiCol_TextSelectedBg] = colorForHead;
	style.Colors[ImGuiCol_DragDropTarget] = colorForHead;
	style.Colors[ImGuiCol_NavHighlight] = colorForHead;
	style.Colors[ImGuiCol_NavWindowingHighlight] = colorForHead;
	style.Colors[ImGuiCol_NavWindowingDimBg] = colorForArea;
	style.Colors[ImGuiCol_ModalWindowDimBg] = colorForArea;
}

inline ImVec4 sc2imv4(irr::video::SColor c) {
	return ImVec4(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
}

// Basic stuff
inline ImVec2 ivec22imvec2(irr::core::recti size) {
	return ImVec2(size.LowerRightCorner.X - size.UpperLeftCorner.X, size.LowerRightCorner.Y - size.UpperLeftCorner.Y);
}
inline ImVec2 ivec22imvec2(irr::core::dimension2du size) {
	return ImVec2(size.Width, size.Height);
}
inline ImVec2 ivec2Pos2imvec2(irr::core::recti size) {
	return ImVec2(size.UpperLeftCorner.X, size.UpperLeftCorner.Y);
}

// Environment
/// @brief Starts the GUI-environment
/// @param dev The IrrlichtDevice
GUIEnvironment::GUIEnvironment(irr::IrrlichtDevice* dev) {
	recv = new CIMGUIEventReceiver();
	pGUI = createIMGUI(dev, recv);

	ImGui::GetIO().IniFilename = NULL;  // Dont create InI files 

	arialFont = pGUI->addFontFromFileTTF("data/fonts/quantico.ttf", 28);
	pGUI->compileFonts();

}
void GUIEnvironment::drawAll() {
	pGUI->startGUI();
	ImGui::PushFont(arialFont);
	if (hasBackgroundWindow) {
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 screenSize = io.DisplaySize;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(screenSize);

	ImGui::Begin("Fullscreen Invisible MainWindow", nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
	}
	for (auto e : children) {
		e->draw();
	}
	if (hasBackgroundWindow) { 
		ImGui::End(); 
	}
	ImGui::PopFont();
	pGUI->drawAll();
}

// Window GUIElement
/// @brief Adds a window
/// @param env the Environment
/// @param rect the bounding box
/// @param text the window text
GUIWindow::GUIWindow(GUIEnvironment* env, std::string text, irr::core::recti rect) : GUIElement(env, rect) {
	_text = text;
	env->addObject(this);
}
void GUIWindow::draw() {
	if (visible) {
		ImGui::SetNextWindowSize(ivec22imvec2(_rect));
		if (!modal) {
			ImGui::Begin(_text.c_str());
			GUIElement::draw();
			ImGui::End();
		}
		else {
			ImGui::BeginPopup(_text.c_str());
			GUIElement::draw();
			ImGui::EndPopup();
		}
	}
}

// Button GUIElement
/// @brief Adds a button
/// @param env the Environment
/// @param rect the bounding box
/// @param text the text
GUIButton::GUIButton(GUIEnvironment* env, irr::core::recti rect, std::string text) : GUIElement(env, rect) {
	_text = text;
	env->addObject(this);
}

void GUIButton::draw() {
	if (visible) {
		if (useColor) {
			ImGui::PushStyleColor(ImGuiCol_Button, sc2imv4(_bnormal));       // Rot
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sc2imv4(_bhovered)); // Orange bei Hover
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, sc2imv4(_bclicked));  // Dunkelrot bei Klick
		}
		ImGui::SetCursorPos(ivec2Pos2imvec2(_rect));
		if (ImGui::Button(_text.c_str(), ivec22imvec2(_rect))) {
			try {
				callback(SG_BUTTON_PRESSED);
			}
			catch (std::exception e) {}
		}
		if (useColor) {
			ImGui::PopStyleColor(3);
		}
		GUIElement::draw();
	}
}

// Group Element
/// @brief Generates a group (eg. for radio Buttons)
/// @param env the GUI-environment
GUIGroup::GUIGroup(GUIEnvironment* env) : GUIElement(env, irr::core::recti()){
	env->addObject(this);
}

void GUIGroup::draw(){
	ImGui::BeginGroup();
	GUIElement::draw();
	ImGui::EndGroup();
}

// SameLine Seperator
GUISameLineSeperator::GUISameLineSeperator(GUIEnvironment* env, int a, int b) : GUIGroup(env), a(a), b(b) {

}

void GUISameLineSeperator::draw() {
	for (auto c : children) {
		c->draw();
		ImGui::SameLine(a, b);
	}
}

// Radio Button
GUIRadioButton::GUIRadioButton(GUIEnvironment* env, irr::core::recti rect, int callbackNum, std::string text) : GUIElement(env, rect), callbackNum(callbackNum) {
	_text = text;
	env->addObject(this);
}

void GUIRadioButton::draw()
{
	if (visible) {
		ImGui::SetCursorPos(ivec2Pos2imvec2(_rect));
		if (ImGui::RadioButton(_text.c_str(), &num, callbackNum)) {
			callback(callbackNum);
		}
		GUIElement::draw();
	}
}

// Invisible Window
GUIInvWindow::GUIInvWindow(GUIEnvironment* env, std::string text, irr::core::recti rect) : GUIWindow(env, text, rect) {
	
}

void GUIInvWindow::draw() {
	ImGui::SetNextWindowPos(ImVec2(_rect.UpperLeftCorner.X, _rect.UpperLeftCorner.Y));
	ImGui::SetNextWindowSize(ImVec2(_rect.LowerRightCorner.X, _rect.LowerRightCorner.Y));

	// Erstellen Sie das Fenster ohne Rahmen, Titelleiste oder Scrollleisten
	ImGui::Begin("Fullscreen Invisible Window", nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);

	GUIElement::draw();

	ImGui::End();

}
#include <iostream>
// Sidebar-Menu
GUISidebarMenu::GUISidebarMenu(GUIEnvironment* env, SGUI_SIDEBAR_MENU_TYPE t, irr::core::recti size, int numRows, std::vector<std::string> names) : GUIElement(env, size) {
	env->addObject(this);

	int buttonWidth = (size.LowerRightCorner - size.UpperLeftCorner).X / numRows;
	int buttonHeight = size.getHeight();

	int bCount = 0;

	static int buttonStates = -1;

	for (int i = 0; i < numRows; i++) {
		GUIButton* b;
		if (t == SGUI_SIDEBAR_UP) {
			b = new GUIButton(env, irr::core::recti(size.UpperLeftCorner.X + bCount, size.UpperLeftCorner.Y, buttonWidth + size.UpperLeftCorner.X + bCount, buttonHeight), names[i]);
			std::cout << size.UpperLeftCorner.X + bCount << std::endl;
			bCount += buttonWidth;
		}
		else if(t==SGUI_SIDEBAR_LEFT) {
			b = new GUIButton(env, irr::core::recti(size.UpperLeftCorner.X + bCount, size.UpperLeftCorner.Y, buttonWidth, buttonHeight), names[i]);
		}
		b->setParent(this);
		b->addCallback([i, this](GUIEvent e) { buttonStates = i; try { _callback(i); } catch (std::exception e) {} btns[i]->setColor(irr::video::SColor(1.0f, 1.0f, 0.0f, 0.0f), irr::video::SColor(1.0f, 1.0f, 0.5f, 0.0f), irr::video::SColor(1.0, 0.5f, 0.0f, 0.0)); int i2 = 0; for (auto b2 : btns) { if (i2 != i) { b2->resetColor(); } i2++;  }});
		btns.push_back(b);
	}
}

void GUISidebarMenu::draw() {
	GUIElement::draw();
}

// RadioButtonGroup
GUIRadioButtonGroup::GUIRadioButtonGroup(GUIEnvironment* env) : GUIGroup(env) {
	GUIBTNN = 0;
}

void GUIRadioButtonGroup::draw(){
	ImGui::BeginGroup();
	for (auto b : btns) {
		b->draw();
	}
	ImGui::EndGroup();
}

void GUIRadioButtonGroup::addRadioButton(GUIRadioButton* b) {
	btns.push_back(b);
	update();
}

void GUIRadioButtonGroup::update() {
	for (auto b : btns) {
		b->addCallback([this, b](int c) { callback(c); GUIBTNN = c; for (auto b : btns) { b->setNum(c); }});
	}
}

// Slider
GUISlider::GUISlider(GUIEnvironment* env, bool is_int_, bool vertical_, float from_, float to_, irr::core::recti pos) : GUIElement(env, pos), val(0), ival(0), from(from_), to(to_), is_int(is_int_), vertical(vertical_) {
	env->addObject(this);
}

void GUISlider::draw() {
	ImGui::SetCursorPos(ivec2Pos2imvec2(_rect));
	if (vertical) {
		if (is_int) {
			if (ImGui::VSliderInt(_text.c_str(), ivec22imvec2(_rect), &ival, from, to)) {
				_callback(ival);
			}
		}
		else {
			if (ImGui::VSliderFloat(_text.c_str(), ivec22imvec2(_rect), &val, from, to)) {
				_callback(val);
			}
		}
	}
	else {
		ImGui::PushItemWidth(ivec22imvec2(_rect).x);
		if (is_int) {
			if (ImGui::SliderInt(_text.c_str(), &ival, from, to)) {
				_callback(ival);
			}
		}
		else {
			if (ImGui::SliderFloat(_text.c_str(), &val, from, to)) {
				_callback(val);
			}
		}
		ImGui::PopItemWidth();
	}
}

// Text-Label