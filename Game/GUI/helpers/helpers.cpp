#include "helpers.h"
#include <pugixml.hpp>
#include <fstream>

using xml = pugi::xml_document;
using node = pugi::xml_node;

std::vector<WorldInGUI> getWorlds(std::string path) {
	xml index;
	auto cap = index.load_file(path.c_str());

	if (!cap) { exit(5); }

	std::vector<WorldInGUI> worlds;

	for(node& n : index.child("Worlds").children("World")){
		WorldInGUI w;
		w.name = n.child("name").text().get();
		w.path = n.child("path").text().get();
		w.icon = n.child("icon").text().get();
		worlds.push_back(w);
	}
	return worlds;
}