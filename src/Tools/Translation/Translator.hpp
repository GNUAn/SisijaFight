#pragma once
#include <string>

namespace translator {
	wchar_t* translate(wchar_t* text);
	std::string translate(std::string text);
	void initTranslator();
}