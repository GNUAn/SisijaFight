#include "Backend.h"

// Globale Instanz der SoLoud-Engine
SoLoud::Soloud gSoloud;

Sound::Sound() : mIsStreamed(false), mIsLooping(false) {
    // Initialisiere die globale SoLoud-Engine
    gSoloud.init();
}

Sound::~Sound() {
    // Aufräumarbeiten
    stop();
}

void Sound::loadSound(const std::string& filename, bool streamed) {
    if (streamed) {
        mStreamedSound.load(filename.c_str());
        mIsStreamed = true;
    }
    else {
        mSound.load(filename.c_str());
        mIsStreamed = false;
    }
}

void Sound::play() {
    if (mIsStreamed) {
        mHandle = gSoloud.play(mStreamedSound);
    }
    else {
        mHandle = gSoloud.play(mSound);
    }

    if (mIsLooping) {
        gSoloud.setLooping(mHandle, true);
    }
}

void Sound::stop() {
    gSoloud.stop(mHandle);
}

void Sound::setVolume(float volume) {
    gSoloud.setVolume(mHandle, volume);
}

void Sound::setPosition(float x, float y, float z) {
    gSoloud.set3dSourcePosition(mHandle, x, y, z);
}

void Sound::setLooping(bool loop) {
    mIsLooping = loop;
    if (mHandle) {
        gSoloud.setLooping(mHandle, loop);
    }
}
