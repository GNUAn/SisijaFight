#pragma once
#include <thread>
#include <string>

class EnetPacket;

class Network {
public:
	void initNetwork();
	void processRequest(ENetPacket* p);
	void send(std::string data);
private:
	void internalThreadInit();
};