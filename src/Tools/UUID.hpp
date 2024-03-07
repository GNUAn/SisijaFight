#pragma once
#include <string>
#include "Tools.hpp"

typedef std::string uuid;

struct music {
    float loopat;
    float loopfrom;
    bool loop;
    uuid id;
};

inline uuid getNewUUID() {
    uuid s;
    for(int i=0; i<random(128,1024); i++){
        s+=toascii(random(0, 256));
    }
    return s;
}