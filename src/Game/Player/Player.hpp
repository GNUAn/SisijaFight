#pragma once
#include <string>
#include <pugixml.hpp>
#include <irrlicht.h>
#include <json.hpp>

using namespace pugi;

class World;
class Weapon;
class IRigidBody;

/// @brief The Config container wich contains the Archivements and the Armor/Weapon
struct PlayerConfiguration{
	std::string weaponPath;
	nlohmann::json archievements;
};

class Player {
public:
	Player(std::string name, std::string path, int ID, World* world, irr::IrrlichtDevice* device, bool localPlayer=false);
	void setDirections(irr::core::vector3df speed, irr::core::vector3df rotation);
private:
	int ID;
	std::string name, path;
	xml_document def;
	Weapon* gun;
	IRigidBody* physics;
	friend class Weapon;
};