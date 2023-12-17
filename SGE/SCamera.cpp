#include "SGU-S.h"

SCamera::SCamera(ISceneManager* smgr) : _smgr(smgr) {
	this->_internal_camera = smgr->addCameraSceneNode();
	this->_internal_camera->setAspectRatio(smgr->getVideoDriver()->getScreenSize().Width / smgr->getVideoDriver()->getScreenSize().Height);
	this->_parent = 0;
}
void SCamera::attachTo(IBoneSceneNode* parent) {
	this->_internal_camera->setFarValue(10000);
	this->_internal_camera->setParent(parent);
	_parent = parent;
}
void SCamera::updateRotationX(f32 rot) {
	this->_internal_camera->setRotation(core::vector3df(0, this->_internal_camera->getRotation().Y, this->_internal_camera->getRotation().Z) + core::vector3df(rot, 0, 0));
}