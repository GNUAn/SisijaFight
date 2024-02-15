#pragma once
#include <vector>

class Network;

class NetworkManager {
public:
	inline void registerHandler(Network* n) {
		handlers.push_back(n);
	}
	inline void handle() {
		for (auto h : handlers) {
			h->handleRoutine();
		}
	}
protected:
	std::vector<Network*> handlers;
};

extern NetworkManager* netmngr;

inline void initNetworkManager() {
	netmngr = new NetworkManager();
}
