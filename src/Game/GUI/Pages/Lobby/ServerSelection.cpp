#include "Lobby.hpp"
#include "Tools/Tools.hpp"
#include "Tools/Ping.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <imspinner.h>

using namespace translator;

bool update=true;

void ServerSelection::updatePing(){
    while(update){
        for(auto& s : servers){
            s.ping = httpPing(s.IP+":8080");
        }
        servers = retrieveServerList("sisijaonline", "/client/get-list");
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

ServerSelection::ServerSelection(){
    std::thread t(&ServerSelection::updatePing, this);
    t.detach();
}

void ServerSelection::draw(GUIEnvironment* env) {
    bool b = true;
    ImGui::PushFont(env->getFont("GUI_DEFAULT_FONT"));
	ImGui::SetNextWindowPos(i2imp(s_rect(30,0,70,100)));
	ImGui::SetNextWindowSize(i2im(s_rect(30,0,70,100)));
    ImGui::Begin("Server Selection", &b);
    if(b==false){ exit(0); }

    static int serverSelected=0;

    ImGui::BeginTable("Servers", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH);
    ImGui::TableSetupColumn(translate("Select").c_str(), 0, 0.05f);
    ImGui::TableSetupColumn(translate("Server Name").c_str(), 0, 0.6f);
    ImGui::TableSetupColumn(translate("Status").c_str(), 0, 0.2f);
    ImGui::TableSetupColumn(translate("Ping").c_str(), 0, 0.1f);
    ImGui::TableHeadersRow();
    int i=0;
    for(auto s : servers){
        if(s.visibility){
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::RadioButton((std::string("## ") + std::to_string(i)).c_str(), &serverSelected, i);
            i++;
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(s.serverName.c_str());
            ImGui::TableSetColumnIndex(3);
            if(s.ping > 0.10f){
                ImGui::Text("%.2f", s.ping);
            }else{
                ImSpinner::SpinnerFadeBars(("##SP1A_" + std::to_string(i)).c_str(), 5, ImSpinner::white, 6.8f, 4, true);
            }
        }
    }
    if(servers.size()==0){
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(1);
        ImGui::Text(translate("Indexing...").c_str());
        ImGui::TableSetColumnIndex(0);
        ImSpinner::SpinnerFadeBars("##SP1A", 5, ImSpinner::white, 6.8f, 4, true);
    }
    ImGui::EndTable();

    ImGui::End();

    ImGui::SetNextWindowPos(i2imp(s_rect(0,0,30,100)));
	ImGui::SetNextWindowSize(i2im(s_rect(0,0,30,100)));
    ImGui::Begin("Social");

    ImGui::End();

    ImGui::PopFont();
}
