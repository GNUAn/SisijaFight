#pragma once
#include <vector>
#include <irrlicht.h>
#include <thread>
#include <unordered_map>
#include <irrBullet.h>

#define PARTICLE_DISTANCE 4
#define PARTICLE_NUMBER_PER_SPLASH 60

struct SPHParticle {
	irr::core::vector3df position;
	irr::scene::ISceneNode* parent;
	long id;
};

struct Paintball {
	irr::core::vector3df position;
	irr::core::vector3df target;
	irr::scene::IMeshSceneNode* model;
	IRigidBody* rigidBody;
};

typedef std::unordered_map<irr::scene::ISceneNode*, SPHParticle> ParticleBySceneNode;

class PaintballSimulator {
public:
	void simulate(int delta);
	void addSplash(irr::core::vector3df);
	void addPaintball(irr::core::vector3df position, irr::core::vector3df target, irrBulletWorld* world);
	void deleteAll();
private:
	void calulateParticle(SPHParticle& p);
	bool checkCollision(SPHParticle a, SPHParticle b);
	void calculateSingleMesh(ParticleBySceneNode& particles, irr::scene::ISceneNode* parent);
	std::vector<SPHParticle*> paticles;
	std::vector<Paintball*> paintballs;
};
