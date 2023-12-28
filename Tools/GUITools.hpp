#ifndef S_GUI_TOOLS
#define S_GUI_TOOLS
#include "../globals.hpp"
#include <irrlicht.h>
#include <string>
#include "Translation/Translator.hpp"

#define gettext(arg) translate(arg)

#define _(arg) gettext(arg)

SColor getNewColor();
int p(int, int);
float p(float, float);
irr::core::recti s_rect(int pX, int pY, int pW, int pH);
std::wstring stringToWString(const std::string& str);


#endif