#include "World.hpp"
#include <pugixml.hpp>

using namespace pugi;

World::World(IrrlichtDevice* dev, std::string path) {
	xml_document d;
	auto success = d.load_file(path.c_str());
	if (!success) { dev->getLogger()->log(success.description(), ELL_ERROR, "WorldLoader, PugiXML"); exit(5); }
	xml_node root = d.child("world");

	xml_node model = root.child("modelFile");
	
	io::path worldPath = dev->getFileSystem()->getFileDir(path.c_str());

	IAnimatedMesh* _mesh = dev->getSceneManager()->getMesh((std::string(worldPath.c_str()) + "/" + std::string(model.text().get())).c_str());
	_node = dev->getSceneManager()->addAnimatedMeshSceneNode(_mesh);
	_node->setMaterialFlag(EMF_LIGHTING, false);

	_physics = createIrrBulletWorld(dev, true, false);
	_physics->setGravity(vector3df(0, -15, 0));
	ICollisionShape* worldShape = new IBvhTriangleMeshShape(_node, _mesh, 0.0f);
	IRigidBody* worldBody = _physics->addRigidBody(worldShape);
	_mesh->drop();

	// TODO: add other xmls
}

void World::loadEntities() {

}

irrBulletWorld* World::getPhysicsWorld() {
	return _physics;
}

IAnimatedMeshSceneNode* World::getSceneNode() {
	return _node;
}

World::~World() {
	_node->remove();
	delete _physics;
}