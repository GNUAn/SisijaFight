#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>
#include <string>
#include <thread>
#include <functional>
#include <json.hpp>

using json = nlohmann::json;

extern int clientID;

typedef std::function<void(json data)> lambda_callback_packet;

class Network {
public:
	void processRequest(ENetPacket* packet);
	void send(const std::string& data);
	void startNetwork(std::string serverAddress, unsigned int serverPort);
	void end();
	void handleRoutine();
	inline void addCallback(lambda_callback_packet f) {

	}
private:
	ENetPeer* peer;
	ENetAddress address;
	ENetHost* client;
	ENetEvent event;
	lambda_callback_packet callback;
	bool _isPeerUsedByThread = false;
	bool isRunning = true;
	void internalThreadInit(std::string serverAddress, uint8_t serverPort);
};

#endif // NETWORK_H
