#include "SGU-S.h"
#include <iostream>

SGES::SGES(IrrlichtDevice* device) {
	
}

void SGES::addObject(ISceneNode* node, IRigidBody* body, std::function<void(SGEvent)> callback) {
	node->setID(_current_id_counter);
	_handler_and_object_id[_current_id_counter] = callback;
	_current_id_counter++;
}

void SGES::handle(irrBulletWorld* world) {
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* objA = contactManifold->getBody0();
		const btCollisionObject* objB = contactManifold->getBody1();

		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++) {
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f) {
				// Kollision erkannt!
				const btCollisionObject* colObjA = static_cast<const btCollisionObject*>(objA);
				const btCollisionObject* colObjB = static_cast<const btCollisionObject*>(objB);

				// Führe hier die spezifische Logik für die Kollisionserkennung durch
				onCollision(colObjA, colObjB);
			}
		}
	}
}
}

SGUI::SGUI(IrrlichtDevice* dev) : _device(dev) {
	auto guienv = _device->getGUIEnvironment();
	guienv->setSkin(guienv->createSkin(EGST_BURNING_SKIN));
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* calibri24 = guienv->getFont("data/fonts/Calibri24.xml");
	if (calibri24)
		skin->setFont(calibri24);

	// Farben und Stil des Skins anpassen
 
	skin->setColor(EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 255)); // Weißer Text
	skin->setColor(EGDC_HIGH_LIGHT, video::SColor(255, 100, 200, 100)); // Hervorhebungsfarbe
	skin->setColor(EGDC_HIGH_LIGHT_TEXT, video::SColor(255, 255, 255, 255)); // Weißer Text für Hervorhebungen
	skin->setColor(EGDC_TOOLTIP_BACKGROUND, video::SColor(255, 50, 50, 50)); // Dunkelgrauer Tooltip-Hintergrund
	skin->setColor(EGDC_TOOLTIP, video::SColor(255, 255, 255, 255)); // Weißer Tooltip-Text

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
			std::cerr << e.what() << std::endl;
		}
}
void SGUI::addObject(IGUIElement* object, std::function<void(SEvent::SGUIEvent)> callback) {
	object->setID(this->_current_id_counter);
	this->_handler_and_object_id[this->_current_id_counter] = callback;
	this->_current_id_counter++;
}