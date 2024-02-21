#define true 1
#define false 0
#include "Session.hpp"
#include "Network/NetworkManager.hpp"
#include "EventReceivers/LobbyEVR.hpp"
#include "EventReceivers/InGameEVR.hpp"
#include "globals.hpp"

int game = false;

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
	_lobby->draw(guienv);
}

/// @brief Starts the Game based on the data of the Lobby
/// @param c the LobbyReturnCode object
/// @param isGMGUIDone Only for GUI reasons. Use isGMGUIDone only, if the GUI of the gamemode has already shown!
void SFSession::startGame(LobbyReturnCode c, bool isGMGUIDone) {
	this->_gamemode = c.gamemode;
	if (_gamemode->hasGUI() && isGMGUIDone) {
		_gamemode->createGUI();
	}
	else {
		startGameInternal(c);
	}
}

/// @brief End the game and clear RAM
void SFSession::endGame() {
	_gamemode->end();
}

/// @brief 
/// @param c 
void SFSession::startGameInternal(LobbyReturnCode c) {
	game = true;
	this->setEventReceiver(S_EVR_GAME);
	World* _world = new World(_device, c.worldPath);
	_world->loadEntities();
	Player* _mainplayer = new Player(NULL, NULL, NULL, nullptr, nullptr, true);
	this->_gamemode->startGame(_world, _mainplayer);
}
void SFSession::setEventReceiver(S_EVR_CODE c) {
	switch (c) {
	case S_EVR_LOBBY:
		_evr = guienv->getEventReceiver();
		_device->setEventReceiver(_evr);
		break;
	case S_EVR_GAME:
		break;
	}
}

void SFSession::loopRoutine() {
	if (_gamemode) 
		_gamemode->handle();
	netmngr->handle();
}
