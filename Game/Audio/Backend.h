#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
#include <string>

extern SoLoud::Soloud gSoloud;

class Sound {
public:
    void loadSound(const std::string& filename, bool streamed = false);
    void play();
    void stop();
    void setVolume(float volume);
    void setPosition(float x, float y, float z);

private:
    SoLoud::Wav mSound;
    SoLoud::WavStream mStreamedSound;
    SoLoud::handle mHandle;
    bool mIsStreamed;
};

#endif // SOUND_PLAYER_H
