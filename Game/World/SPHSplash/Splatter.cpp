#include "Splatter.hpp"
#include "../../globals.h"
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

void PaintballSimulator::addPaintball(vector3df start, vector3df target, irrBulletWorld* world) {
	Paintball* paintball = new Paintball();
	paintball->position = start;
	paintball->target = target;
	paintball->model = device->getSceneManager()->addSphereSceneNode(1.0f, 16, 0, -1, start);

	ICollisionShape* shape = new ISphereShape(paintball->model, 1.0f, false);
	IRigidBody* body = world->addRigidBody(shape);
	vector3df direction = target.normalize();
	body->setLinearVelocity(direction);
	paintball->rigidBody = body;

	paintballs.push_back(paintball);
}