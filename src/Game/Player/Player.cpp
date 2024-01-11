#include "Player.hpp"
#include <pugixml.hpp>
#include "../World/World.hpp"
#include <json.hpp>
#include <irrlichtDevice.h>
#include "Weapon.hpp"


/// @brief Create a Player
/// @param name The name of the Player (Gamertag)
/// @param path The XML-Player-Definition path
/// @param ID The ClientID
/// @param world The World for Physics reasons
/// @param device The Irrlicht Device
/// @param localPlayer Defines if the Player is the MainPlayer of this Computer
Player::Player(std::string name, std::string path, int ID, World* world, irr::IrrlichtDevice* device, bool localPlayer)
{

}
