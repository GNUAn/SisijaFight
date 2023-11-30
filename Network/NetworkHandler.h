#pragma once
#include <thread>
#include <string>
#include <enet.h>

class Network {
public:
	void initNetwork();
	void processRequest(ENetPacket* p);
	void send(std::string data);
private:
	void internalThreadInit();
};