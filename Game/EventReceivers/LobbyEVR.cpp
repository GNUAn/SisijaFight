#include "LobbyEVR.h"
#include "../../SGE/SGU-S.h"

bool GUIEventReceiver::OnEvent(const SEvent& event) {
	if (event.EventType == EET_GUI_EVENT) {
		subsystem->handle(event.GUIEvent);
		return true;
	}
}