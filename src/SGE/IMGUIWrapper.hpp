#pragma once
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIrrlicht.h>
#include <string>
#include <vector>
#include <functional>
#include <irrlicht.h>

using namespace IrrIMGUI;

enum GUIEvent {
	SG_BUTTON_PRESSED, SG_TEXTFIELD_CHANGED
};

enum ThemeColor {
	Red,
	Green,
	White,
	Blue,
	Yellow
};

void SetGUIThemeColor(ThemeColor themeColor);
ImVec2 ivec22imvec2(irr::core::recti size);
ImVec2 ivec22imvec2(irr::core::dimension2du size);
ImVec2 ivec2Pos2imvec2(irr::core::recti size);

class GUIElement;

class GUIEnvironment {
public:
	GUIEnvironment(irr::IrrlichtDevice* device);
	void drawAll();
	inline void addObject(GUIElement* e) {
		children.push_back(e);
	}
	/// @brief Disable this if you need no background window (e.g. for HUD)
	inline void setDefaultBackgroundWindow(bool c) {
		hasBackgroundWindow = c;
	}
	inline void removeObject(GUIElement* e) {
		try {
			auto it = std::remove(children.begin(), children.end(), e);
			children.erase(it, children.end());
		} catch(std::exception e){}
	}
	inline CIMGUIEventReceiver* getEventReceiver() {
		return recv;
	}
private:
	GUIElement* root;
	CIMGUIEventReceiver* recv;
	IIMGUIHandle* pGUI;
	std::vector<GUIElement*> children;
	bool hasBackgroundWindow=true;
	ImFont* arialFont;
};

class GUIElement {
public:
	inline GUIElement(GUIEnvironment* env, irr::core::recti rect) : _env(env), _rect(rect) {
		// ...
	}
	inline virtual void draw(){
		for (auto c : children) {
			c->draw();
		}
	}
	inline virtual void remove() {
		_env->removeObject(this);
	}
	inline virtual void setText(std::string text) {
		_text = text;
	}
	inline virtual void addChild(GUIElement* e) {
		children.push_back(e);
	}
	inline virtual void setParent(GUIElement* p) {
		p->addChild(this);
		_env->removeObject(this);
	}
	inline virtual void addCallback(std::function<void(GUIEvent e)> cback) {
		callback = cback;
	}
	inline virtual void setVisible(bool v) {
		visible = v;
	}
	inline virtual void setActive(bool a) {
		_active = a;
	}
protected:
	irr::core::recti _rect;
	std::vector<GUIElement*> children;
	std::function<void(GUIEvent)> callback;
	std::string _text;
	GUIEnvironment* _env;
	bool _active = true;
	bool visible = true;
};

class GUIGroup : public GUIElement{
public:
	GUIGroup(GUIEnvironment* env);
	void draw() override;
};

class GUISameLineSeperator : public GUIGroup {
public:
	GUISameLineSeperator(GUIEnvironment* env, int a, int b);
	void draw() override;
protected:
	int a, b;
};

class GUIRadioButton : public GUIElement{
public:
	GUIRadioButton(GUIEnvironment* env, int callbackNum, std::string text);
	void draw();
protected:
	int callbackNum;
};

class GUIWindow : public GUIElement {
public:
	GUIWindow(GUIEnvironment* env, std::string text, irr::core::recti rect);
	void draw() override;
	inline void setDraggable(bool c);
	inline void setModal(bool c) {
		modal = c;
	}
protected:
	bool active;
	bool modal;
};

class GUIInvWindow : public GUIWindow {
public:
	GUIInvWindow(GUIEnvironment* env, std::string text, irr::core::recti rect);
	void draw() override;
};

class GUIButton : public GUIElement {
public:
	GUIButton(GUIEnvironment* env, irr::core::recti rect, std::string text);
	inline void setColor(irr::video::SColor bnormal, irr::video::SColor bhovered, irr::video::SColor bclicked) {
		_bnormal = bnormal;
		_bhovered = bhovered;
		_bclicked = bclicked;
		useColor = true;
	}
	void resetColor() {
		useColor = false;
	}
	void draw() override;
private:
	irr::video::SColor _bnormal, _bhovered, _bclicked;
	bool useColor=false;
};

class GUISidebarMenu : public GUIElement {
public:
	enum SGUI_SIDEBAR_MENU_TYPE { SGUI_SIDEBAR_LEFT, SGUI_SIDEBAR_UP };
	GUISidebarMenu(GUIEnvironment* env, SGUI_SIDEBAR_MENU_TYPE t, irr::core::recti size, int numRows, std::vector<std::string> names);
	void draw();
	inline void addCallback(std::function<void(int e)> cback) {
		_callback = cback;
	}
protected:
	std::function<void(int e)> _callback;
	std::vector<GUIButton*> btns;
};

class GUIImage : public GUIElement {
public:
	GUIImage(GUIEnvironment* env, irr::core::recti rect);
	void draw() override;
	void setScaleImage(bool c);
	void setImage(irr::video::ITexture* tex);
	void setImage(irr::video::IImage* img);
};
