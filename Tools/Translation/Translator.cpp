#include "Translator.hpp"
#include "../Configurator.hpp"
#include <pugixml.hpp>
#include <json.hpp>
#include <fstream>
#include <cstring>

using namespace pugi;
using json = nlohmann::json;

json translationFile;

bool isDefaultLanguage = false;

void initTranslator() {
	SConfig c = globalConfig;

	isDefaultLanguage = c.lang == "en";
	if (isDefaultLanguage) { return; }
	
	xml_document langs;
	if (!langs.load_file("data/translations/languages.xml")) { exit(424); }

	xml_node root = langs.child("languages");

	xml_node selectedLanguage;
	std::string languageCode = c.lang;

	for (auto n : root.children("language")) {
		if (n.attribute("code").as_string() == languageCode) {
			selectedLanguage = n;
		}
	}
	if (!selectedLanguage) { exit(423); }
	std::string jsonPath = selectedLanguage.text().get();
	
	std::fstream file(("data/translations/" + jsonPath).c_str());
	file >> translationFile;
}


std::string translate(std::string text) {
	if (!isDefaultLanguage) {
		return translationFile[text];
	}
	else {
		return text;
	}
}