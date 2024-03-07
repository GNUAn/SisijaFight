#pragma once
#include <irrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <string>
#include <imgui.h>
#include <unordered_map>

using namespace IrrIMGUI;
using namespace irr;
using namespace core;

class GUIPage;
class GUIEnvironment {
public:
	GUIEnvironment(irr::IrrlichtDevice* device);
	void drawAll();
    void registerNewFont(std::string path, float size, std::string id);
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
    std::unordered_map<std::string, ImFont*> registeredFonts;
};