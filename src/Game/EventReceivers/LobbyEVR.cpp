#include "LobbyEVR.hpp"
#include "../../SGE/SGU-S.hpp"

bool GUIEventReceiver::OnEvent(const SEvent& event) {
	if (event.EventType == EET_GUI_EVENT) {
		subsystem->handle(event.GUIEvent);
		return true;
	}
	return false;
}