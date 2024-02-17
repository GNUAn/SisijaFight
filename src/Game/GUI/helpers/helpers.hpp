#pragma once
#include <vector>
#include <string>

struct WorldInGUI {
	std::string name;
	std::string path;
	std::string icon;
};
struct ServerInGUI {
	std::string IP;
};

std::vector<WorldInGUI> getWorlds(std::string path);

std::vector<ServerInGUI> findServers();
