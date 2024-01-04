#pragma once
#include <pugixml.hpp>

struct SFConfig {
	//Localisation
	const char* version = "0.2.1";
	const char* lang = "de";
	//Player specific stuff
	const char* tag, * password;
	//...
};

extern SFConfig globalConfig;

void checkProcessor();