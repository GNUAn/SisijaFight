#include "Session.h"
#include "../Network/NetworkHandler.h"
#include "EventReceivers/LobbyEVR.h"
#include "EventReceivers/InGameEVR.h"
#include "../globals.h"

bool game = false;

GameMode* SFSession::gamemode() {
	return _gamemode;
}
Lobby* SFSession::lobby() {
	return _lobby;
}
void SFSession::init() {
	this->_network->initNetwork();
	this->setEventReceiver(S_EVR_LOBBY);
	this->_lobby = new Lobby();
	_lobby->draw(_device);
}
void SFSession::startGame(LobbyReturnCode& c) {
	game = true;
	this->setEventReceiver(S_EVR_GAME);
	this->_gamemode = c.gamemode;

}
void SFSession::setEventReceiver(S_EVR_CODE c) {
	switch (c) {
	case S_EVR_LOBBY:
		_evr = new GUIEventReceiver(GUIEngine);
		_device->setEventReceiver(_evr);
		break;
	case S_EVR_GAME:
		break;
	}
}