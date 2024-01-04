#include "SGU-S.hpp"
#include <iostream>

SGES::SGES(IrrlichtDevice* device) {
	
}

void SGES::addObject(ISceneNode* node, IRigidBody* body, std::function<void(SGEvent)> callback) {
	node->setID(_current_id_counter);
	_handler_and_object_id[_current_id_counter] = callback;
	_current_id_counter++;
}


SGUI::SGUI(IrrlichtDevice* dev) : _device(dev) {
	auto guienv = _device->getGUIEnvironment();
	guienv->setSkin(guienv->createSkin(EGST_WINDOWS_METALLIC));
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* calibri24 = guienv->getFont("data/fonts/Calibri24.xml");
	if (calibri24)
		skin->setFont(calibri24);

	// Farben und Stil des Skins anpassen
 
	skin->setColor(EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 255)); // Wei�er Text
	skin->setColor(EGDC_HIGH_LIGHT, video::SColor(255, 100, 200, 100)); // Hervorhebungsfarbe
	skin->setColor(EGDC_HIGH_LIGHT_TEXT, video::SColor(255, 255, 255, 255)); // Wei�er Text f�r Hervorhebungen
	skin->setColor(EGDC_TOOLTIP_BACKGROUND, video::SColor(255, 50, 50, 50)); // Dunkelgrauer Tooltip-Hintergrund
	skin->setColor(EGDC_TOOLTIP, video::SColor(255, 255, 255, 255)); // Wei�er Tooltip-Text

}

void SGUI::clearAll() {
	IGUIElement* root;
	root = _device->getGUIEnvironment()->getRootGUIElement();
	for (auto& child : root->getChildren()) {
		child->remove();
		child->drop();
	}
	this->_handler_and_object_id.clear();
}

void SGUI::handle(SEvent::SGUIEvent event) {
		try {
			this->_handler_and_object_id[event.Caller->getID()](event);
		}
		catch (std::exception& e) {
			_device->getLogger()->log(e.what(), ELL_WARNING, "SGUI-Handler, Lambda runner");
		}
}
/// @brief Register a Irrlicht GUI-Element with Event callback
/// @param object The IGUIElement
/// @param callback The lambda Function to run
void SGUI::addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback) {
	object->setID(this->_current_id_counter);
	this->_handler_and_object_id[this->_current_id_counter] = callback;
	this->_current_id_counter++;
}