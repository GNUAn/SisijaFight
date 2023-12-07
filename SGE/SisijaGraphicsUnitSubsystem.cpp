#include "SGU-S.h"
#include <iostream>

SGES::SGES(IrrlichtDevice* device) {
	
}

SGUI::SGUI(IrrlichtDevice* dev) : _device(dev) {
	auto guienv = _device->getGUIEnvironment();
    IGUISkin* skin = guienv->getSkin();
    IGUIFont* calibri24 = guienv->getFont("data/fonts/Calibri24.xml");
    if (calibri24)
        skin->setFont(calibri24);

    // Farben und Stil des Skins anpassen
    skin->setColor(EGDC_WINDOW, video::SColor(255, 60, 70, 80)); // Dunkelblauer Hintergrund
    skin->setColor(EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 255)); // Weißer Text
    skin->setColor(EGDC_3D_FACE, video::SColor(255, 0, 150, 0)); // Grünliche Buttons
    skin->setColor(EGDC_3D_SHADOW, video::SColor(255, 0, 100, 0)); // Dunkleres Grün für Schatten
    skin->setColor(EGDC_HIGH_LIGHT, video::SColor(255, 100, 200, 100)); // Hervorhebungsfarbe
    skin->setColor(EGDC_HIGH_LIGHT_TEXT, video::SColor(255, 255, 255, 255)); // Weißer Text für Hervorhebungen
    skin->setColor(EGDC_TOOLTIP_BACKGROUND, video::SColor(255, 50, 50, 50)); // Dunkelgrauer Tooltip-Hintergrund
    skin->setColor(EGDC_TOOLTIP, video::SColor(255, 255, 255, 255)); // Weißer Tooltip-Text

}

void SGUI::handle(SEvent::SGUIEvent event) {
        try {
            this->_handler_and_object_id[event.Caller->getID()](event);
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
}
void SGUI::addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback) {
	object->setID(this->_current_id_counter);
	this->_handler_and_object_id[this->_current_id_counter] = callback;
    this->_current_id_counter++;
}