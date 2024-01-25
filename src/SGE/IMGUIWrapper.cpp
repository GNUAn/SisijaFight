#include "IMGUIWrapper.hpp"

// Basic stuff
inline ImVec2 ivec22imvec2(irr::core::recti size) {
	return ImVec2(size.getWidth(), size.getHeight());
}
inline ImVec2 ivec22imvec2(irr::core::dimension2du size) {
	return ImVec2(size.Width, size.Height);
}

// Environment
/// @brief Starts the GUI-environment
/// @param dev The IrrlichtDevice
GUIEnvironment::GUIEnvironment(irr::IrrlichtDevice* dev) {
	recv = new CIMGUIEventReceiver();
	pGUI = createIMGUI(dev, recv);
}
void GUIEnvironment::drawAll() {
	pGUI->startGUI();
	for (auto e : children) {
		e->draw();
	}
	pGUI->drawAll();
}

// Window GUIElement
/// @brief Adds a window
/// @param env the Environment
/// @param rect the bounding box
/// @param text the window text
GUIWindow::GUIWindow(GUIEnvironment* env, irr::core::recti rect, std::string text) : GUIElement(env, rect) {
	_text = text;
	env->addObject(this);
}
void GUIWindow::draw() {
	if (visible) {
		ImGui::Begin(_text.c_str());
		for (auto c : children) {
			c->draw();
		}
		ImGui::End();
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
		if (ImGui::Button(_text.c_str(), ivec22imvec2(_rect))) {
			try {
				callback(SG_BUTTON_PRESSED);
			}
			catch (std::exception e) {}
		}
		for (auto c : children) {
			c->draw();
		}
	}
}