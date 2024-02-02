#include <httplib.h>
#include <json.hpp>
#include <liboai.h>

class GPTResponder {
public:
	GPTResponder();
	void respond(std::string context);
	void respondChat(nlohmann::json chat, std::string message);
private:
	
};
