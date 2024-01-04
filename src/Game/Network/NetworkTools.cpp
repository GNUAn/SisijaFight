#include "NetworkTools.hpp"

#include <httplib.h>
#include <pugixml.hpp>

using namespace httplib;
using namespace pugi;

std::vector<server> getOnlineServers() {
	// Get the current online Servers from the Main Server
	
	Client net("sisijafight.org");

	auto r = net.Get("/get_current_servers");

	xml_document p;

	p.load_string(r->body.c_str());

	std::vector<server> s;
	return s;
}