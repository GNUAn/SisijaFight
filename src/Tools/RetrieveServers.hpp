#pragma once
#include <httplib.h>
#include <json.hpp>
#include <iostream>
#include <vector>

struct ServerInfo {
    std::string serverName;
    int serverPort;
    int maximumPlayersPerRoom;
    bool hasRooms;
    int numRooms;
    bool visibility;
    bool useIp;
    std::string IP;
    std::string password;
    float ping;
};

inline std::vector<ServerInfo> retrieveServerList(const std::string& host, const std::string& endpoint) {
    httplib::Client cli(host.c_str(), 8080);
    auto res = cli.Get(endpoint.c_str());

    std::vector<ServerInfo> servers;

    if (res && res->status == 200) {
        auto json = nlohmann::json::parse(res->body);
        for (const auto& item : json) {
            ServerInfo info{
                item["serverName"],
                item["serverPort"],
                item["maximumPlayersPerRoom"],
                item["hasRooms"],
                item["numRooms"],
                item["visibility"],
                item["useIp"],
                item["clientIp"],
                item["password"]
            };
            servers.push_back(info);
        }
    } else {
        std::cerr << "Error: ";
        if (res) {
            std::cerr << res->status << std::endl;
        } else {
            std::cerr << "No response!" << std::endl;
        }
    }

    return servers;
}
