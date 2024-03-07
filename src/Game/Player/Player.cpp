#include "Player.hpp"
#include "../World/World.hpp"
#include <irrlichtDevice.h>
#include "Weapon.hpp"
#include <irrlicht.h>
#include "globals.hpp"
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace io;
using namespace pugi;

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

/// @brief Set the velocities of the Players
/// @param speed The target
/// @param rotation the Rotation
void Player::setDirections(irr::core::vector3df speed, irr::core::vector3df rotation) {
    irr::core::matrix4 mat;
    mat.setRotationDegrees(rotation);
    irr::core::vector3df rotatedSpeed = speed; 
    mat.transformVect(rotatedSpeed, speed);
    physics->setLinearVelocity(rotatedSpeed);
}

void Player::spawn(vector3df position){
    
}
