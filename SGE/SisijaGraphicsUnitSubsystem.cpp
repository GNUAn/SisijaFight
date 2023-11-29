#include "SGU-S.h"

SGES::SGES(IrrlichtDevice* device) {

}

void SGUI::handle(SEvent::SGUIEvent event) {
	this->_handler_and_object_id[event.Caller->getID()](event);
}
void SGUI::addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback) {
	object->setID(this->_current_id_counter);
	this->_handler_and_object_id[this->_current_id_counter] = callback;
}