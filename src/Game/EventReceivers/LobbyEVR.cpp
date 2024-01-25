#include "LobbyEVR.hpp"
#include "../../SGE/SGU-S.hpp"
#include "../../globals.hpp"

bool GUIEventReceiver::OnEvent(const SEvent& event) {
	return guienv->getEventReceiver()->OnEvent(event);
}