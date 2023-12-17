#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>
#include <string>
#include <thread>

extern int clientID;

class Network {
public:
    void processRequest(ENetPacket* packet);
    void send(const std::string& data);
    void internalThreadInit();
    void initNetwork();
    void end();
};

#endif // NETWORK_H
