#include "Session.hpp"
#include "../Network/NetworkHandler.hpp"
#include "EventReceivers/LobbyEVR.hpp"
#include "EventReceivers/InGameEVR.hpp"
#include "../globals.hpp"

bool game = false;

GameMode* SFSession::gamemode() {
	return _gamemode;
}
Lobby* SFSession::lobby() {
	return _lobby;
}
void SFSession::init() {
	this->setEventReceiver(S_EVR_LOBBY);
	this->_lobby = new Lobby();
	_lobby->draw(_device);
}
void SFSession::startGame(LobbyReturnCode c, bool isGMGUIDone) {
	this->_gamemode = c.gamemode;
	if (_gamemode->hasGUI()) {
		_gamemode->createGUI(_device->getGUIEnvironment());
	}
	else {
		startGameInternal(c);
	}
}
void SFSession::endGame() {
	delete _world;
	delete _mainplayer;
	_network->end();
}
void SFSession::startGameInternal(LobbyReturnCode c) {
	game = true;
	this->setEventReceiver(S_EVR_GAME);
	this->_world = new World(_device, c.worldPath);
	this->_world->loadEntities();
	this->_network->startNetwork(c.serverAddress, SF_STANDARD_NETWORK_PORT);
	this->_gamemode->startGame(_world, _mainplayer, _device);
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