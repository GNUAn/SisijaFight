#pragma once
#include <vector>
#include <string>

struct WorldInGUI {
	std::string name;
	std::string path;
	std::string icon;
};

std::vector<WorldInGUI> getWorlds(std::string path);