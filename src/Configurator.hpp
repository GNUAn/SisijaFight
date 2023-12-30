#include <pugixml.hpp>

struct SConfig {
	//Localisation
	const char* version = "0.2.1";
	const char* lang = "de";
	//Player specific stuff
	const char* tag, * password;
	//...
};

extern SConfig globalConfig;

void getConfiguraion();