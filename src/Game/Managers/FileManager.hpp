#pragma once
#include <irrlicht.h>
#include <string>

#include <iostream>
#include <string>

#ifdef _WIN32
#define USER_PATH std::getenv("APPDATA") + std::string("\\SisijaFight\\")
#define TEMP_PATH std::getenv("TEMP") + std::string("\\")

#elif defined(__linux__)
#define USER_PATH std::string(getenv("HOME")) + std::string("/.SisijaFight/")
#define TEMP_PATH "/tmp/"

#elif defined(__APPLE__)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#define USER_PATH std::string(getenv("HOME")) + std::string("/Library/Application Support/SisijaFight/")
#define TEMP_PATH "/tmp/"
#endif

enum SEncoding {
    SE_UTF8, SE_ANSI, SE_BIN
};

class FileManager {
public:
    void mountArchive(irr::io::path path);
    void unmountAllArchives();
    void removeAllTemporaryFiles();
    void saveFile(irr::io::path path, std::string content, SEncoding encoding);
    void saveTemporaryFile(irr::io::path relative_path, std::string content, SEncoding encoding);
    void saveUserFile(irr::io::path relative_path, std::string content, SEncoding encoding);
    inline std::string getUserPath() const {return USER_PATH;}
    inline std::string getTemporaryPath() const {return TEMP_PATH;}
    irr::io::path searchFile(std::string name);
private:

};