#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>
#include <string>
#include <thread>
#include <functional>

extern int clientID;

class Network {
public:
	void processRequest(ENetPacket* packet);
	void send(const std::string& data);
	void startNetwork(std::string serverAddress, unsigned int serverPort);
	void end();
private:
	ENetPeer* peer;
	ENetAddress address;
	ENetHost* client;
	ENetEvent event;
	std::function<void(std::string)> fCallback;
	bool _isPeerUsedByThread = false;
	bool isRunning = true;
	void internalThreadInit(std::string serverAddress, uint8_t serverPort);
};

#endif // NETWORK_H
