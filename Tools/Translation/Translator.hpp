#pragma once
#include <tinygettext/tinygettext.hpp>
#include <string>

wchar_t* translate(wchar_t* text);
const char* translate(const char* text);
std::string translate(std::string text);
void initTranslator();