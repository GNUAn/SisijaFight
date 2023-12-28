#include <pugixml.hpp>
#include <string>

struct SConfig {
	//Localisation
	std::string version = "0.2.1";
	std::string lang = "de";
	//Player specific stuff
	std::string tag, password;
	//...
};

extern SConfig globalConfig;

SConfig getConfiguraion();