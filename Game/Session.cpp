#include "Session.h"
#include "../Network/NetworkHandler.h"

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
}
void SFSession::startGame(LobbyReturnCode& c) {
	game = true;
	this->setEventReceiver(S_EVR_GAME);
	this->_gamemode = c.gamemode;

}
void SFSession::setEventReceiver(S_EVR_CODE c) {
	switch (c) {
	case S_EVR_LOBBY:
		break;
	}
}