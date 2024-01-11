#include "Session.hpp"
#include "../Network/NetworkHandler.hpp"
#include "EventReceivers/LobbyEVR.hpp"
#include "EventReceivers/InGameEVR.hpp"
#include "../globals.hpp"

bool game = false;

/// @brief Gets the gamemode
/// @return The pointer to the Gamemode
GameMode* SFSession::gamemode() {
	return _gamemode;
}


/// @brief Gets the lobby GUIPage
/// @return The Pointer to the lobby GUIPage
Lobby* SFSession::lobby() {
	return _lobby;
}

/// @brief Ititializes the Session
void SFSession::init() {
	this->setEventReceiver(S_EVR_LOBBY);
	this->_lobby = new Lobby();
	_lobby->draw(_device);
}

/// @brief Starts the Game based on the data of the Lobby
/// @param c the LobbyReturnCode object
/// @param isGMGUIDone Only for GUI reasons. Use isGMGUIDone only, if the GUI of the gamemode has already shown!
void SFSession::startGame(LobbyReturnCode c, bool isGMGUIDone) {
	this->_gamemode = c.gamemode;
	if (_gamemode->hasGUI() && isGMGUIDone) {
		_gamemode->createGUI(_device->getGUIEnvironment());
	}
	else {
		startGameInternal(c);
	}
}

/// @brief End the game and clear RAM
void SFSession::endGame() {
	delete _world;
	delete _mainplayer;
	_network->end();
}

/// @brief 
/// @param c 
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