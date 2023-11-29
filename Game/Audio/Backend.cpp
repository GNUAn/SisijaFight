#include "Backend.h"


// Globale Instanz der SoLoud-Engine
SoLoud::Soloud gSoloud;

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