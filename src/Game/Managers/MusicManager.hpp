#pragma once
#include "FileManager.hpp"
#include "Tools/UUID.hpp"

class MusicManager {
public:
    uuid loadFromAFile(irr::io::path audio_file_path);
    uuid loadFromDefFile(irr::io::path audio_file_path);
    void pauseAll();

};

extern MusicManager* mmngr;