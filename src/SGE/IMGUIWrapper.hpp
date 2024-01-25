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

ImVec2 ivec22imvec2(irr::core::recti size);
ImVec2 ivec22imvec2(irr::core::dimension2du size);

class GUIElement;

class GUIEnvironment {
public:
	GUIEnvironment(irr::IrrlichtDevice* device);
	void drawAll();
	inline void addObject(GUIElement* e) {
		children.push_back(e);
	}
	inline void removeObject(GUIElement* e) {
		auto it = std::remove(children.begin(), children.end(), e);
		children.erase(it, children.end());
	}
	inline CIMGUIEventReceiver* getEventReceiver() {
		return recv;
	}
private:
	GUIElement* root;
	CIMGUIEventReceiver* recv;
	IIMGUIHandle* pGUI;
	std::vector<GUIElement*> children;
};

class GUIElement {
public:
	inline GUIElement(GUIEnvironment* env, irr::core::recti rect) : _env(env), _rect(rect) {
		// ...
	}
	virtual void draw() = 0;
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
protected:
	irr::core::recti _rect;
	std::vector<GUIElement*> children;
	std::function<void(GUIEvent)> callback;
	std::string _text;
	GUIEnvironment* _env;
	bool visible = true;
};

class GUIWindow : public GUIElement {
public:
	GUIWindow(GUIEnvironment* env, irr::core::recti rect, std::string text);
	void draw() override;
	inline void setDraggable(bool c);
	inline void setModal(bool c);
protected:
	bool active;
	bool modal;
};

class GUIButton : public GUIElement {
public:
	GUIButton(GUIEnvironment* env, irr::core::recti rect, std::string text);
	void draw() override;
	void setActive(bool active);
protected:
	bool active;
};

class GUIImage : public GUIElement {
public:
	GUIImage(GUIEnvironment* env, irr::core::recti rect);
	void draw() override;
	void setScaleImage(bool c);
	void setImage(irr::video::ITexture* tex);
	void setImage(irr::video::IImage* img);
};
