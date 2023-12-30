#pragma once

#include <string>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

class Sound {
public:
    Sound();
    ~Sound();

    void loadSound(const std::string& filename, bool streamed);
    void play();
    void stop();
    void setVolume(float volume);
    void setPosition(float x, float y, float z);
    void setLooping(bool loop);

private:
    SoLoud::Wav mSound;
    SoLoud::WavStream mStreamedSound;
    SoLoud::handle mHandle;
    bool mIsStreamed;
    bool mIsLooping;
};

// Globale Instanz der SoLoud-Engine
extern SoLoud::Soloud gSoloud;
