#include <enet/enet.h>
#include <json.hpp>
#include <iostream>
#include <zlib.h>
#include <vector>
#include <string>
#include <thread>
#include "NetworkHandler.h"

ENetPeer* peer;
int clientID = 62;

// Kompressions- und Dekompressionsfunktionen
std::vector<Bytef> compressData(const std::string& str) {
    uLongf compressedSize = compressBound(str.size());
    std::vector<Bytef> compressedData(compressedSize);
    compress(compressedData.data(), &compressedSize, reinterpret_cast<const Bytef*>(str.data()), str.size());
    compressedData.resize(compressedSize);
    return compressedData;
}

std::string decompressData(const Bytef* compressedData, size_t compressedSize) {
    uLongf decompressedSize = compressedSize * 2;
    std::vector<Bytef> decompressedData(decompressedSize);
    while (Z_BUF_ERROR == uncompress(decompressedData.data(), &decompressedSize, compressedData, compressedSize)) {
        decompressedSize *= 2;
        decompressedData.resize(decompressedSize);
    }
    return std::string(reinterpret_cast<char*>(decompressedData.data()), decompressedSize);
}

void Network::processRequest(ENetPacket* packet) {
    std::string decompressedData = decompressData(packet->data, packet->dataLength);
    try {
        auto json = nlohmann::json::parse(decompressedData);
        if (json.contains("CLIENTID")) {
            clientID = json["CLIENTID"].get<int>();
            std::cout << "Client ID: " << clientID << std::endl;
        }
        // Session->gamemode()->handleNetwork(json);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Network::send(const std::string& data) {
    auto compressedData = compressData(data);
    ENetPacket* packet = enet_packet_create(compressedData.data(), compressedData.size(), ENET_PACKET_FLAG_RELIABLE);
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

void Network::initNetwork() {
    std::thread networkThread(&Network::internalThreadInit, this);
    networkThread.detach();
}

void Network::end() {
    if (peer != nullptr) {
        ENetEvent event;

        enet_peer_disconnect(peer, 0);

        while (enet_host_service(peer->host, &event, 3000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                return;
            }
        }

        enet_peer_reset(peer);
        puts("Disconnection forced.");
    }
}
