#pragma once
#include <string>
#include <vector3d.h>

class Player;

class Weapon {
public:
    Weapon(std::string path, Player* player);
    void init();
private:
    void shoot(irr::core::vector3df target);
    void updateShot();
    friend class Player;
};