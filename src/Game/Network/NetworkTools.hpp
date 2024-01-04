#pragma once
#include <vector>
#include <string>

struct server {
	std::string ip;
	std::string name;
	std::string description;
	int playersOnline;
	bool currentlyAvailable;
	bool isLocalNetwork;
};

std::vector<server> getOnlineServers();