#pragma once
#include <irrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <string>
#include <vector>
#include <imgui.h>
#include <unordered_map>
#include "Widget.hpp"

using namespace IrrIMGUI;
using namespace irr;
using namespace core;

class GUIPage;
class GUIEnvironment {
public:
	GUIEnvironment(irr::IrrlichtDevice* device);
	void drawAll();
    void registerNewFont(std::string path, float size, std::string id);
    void registerNewImage(std::string path, std::string id);
    void addWidget(GUIWidget* w) { widgets.push_back(w); }
    void unsubscribeWidget(int id) { widgets.erase(widgets.begin() + id); }
    inline ImTextureID getImage(std::string id);
    inline ImFont* getFont(std::string id)              { return registeredFonts[id]; }
	inline irr::video::IVideoDriver* getVideoDriver()   { return _device->getVideoDriver(); }
	inline IIMGUIHandle* getIMGUI()                     { return pGUI; }
	inline CIMGUIEventReceiver* getEventReceiver()      { return recv; }
    inline void setActiveGUIPage(GUIPage* p)            { activeGUIPage=p; }
private:
	irr::IrrlichtDevice* _device;
	CIMGUIEventReceiver* recv;
	IIMGUIHandle* pGUI;
    GUIPage* activeGUIPage;
    std::vector<GUIWidget*> widgets;
    int _widgetIdCount=0;
    std::unordered_map<std::string, ImFont*> registeredFonts;
    std::unordered_map<std::string, ImTextureID> registeredImages;
};