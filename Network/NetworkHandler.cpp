#include "NetworkHandler.h"
#include <json.hpp>
#include "../globals.h"

ENetPeer* peer;

u16 clientID = 62;

u32 lt;

void Network::processRequest(ENetPacket* packet) {
	std::string data(reinterpret_cast<char*>(packet->data));

	try {
		auto json = nlohmann::json::parse(data);

		if (json.contains("CLIENTID")) {
			clientID = json["CLIENTID"].get<int>();
			std::cout << "Client ID: " << clientID << std::endl;
		}
		session.gamemode().hanldeNetwork(json);
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Network::initNetwork() {
	std::thread netwrk(&Network::internalThreadInit, this);
	netwrk.detach();
}

void Network::send(const std::string data) {
	ENetPacket* packet = enet_packet_create(data.c_str(), data.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(peer->host);
}


void Network::internalThreadInit() {
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;

	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return;
	}
	atexit(enet_deinitialize);

	client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);
	if (client == NULL) {
		fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
		return;
	}

	enet_address_set_host(&address, "localhost");
	address.port = 65432;
	peer = enet_host_connect(client, &address, 2, 0);
	if (peer == NULL) {
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		return;
	}

	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
		puts("Connection to SisijaFight.local succeeded.");
	}
	else {
		enet_peer_reset(peer);
		puts("Connection to SisijaFight.local failed.");
	}
	while (true) {
		while (enet_host_service(client, &event, 1000) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				processRequest(event.packet);
				enet_packet_destroy(event.packet);
				break;
			}
		}
	}
	enet_host_destroy(client);
}