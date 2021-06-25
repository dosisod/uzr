#include <iostream>

#include "httplib.h"

using namespace httplib;

void api_health(const Request&, Response& res) {
	res.set_content("ok", "text/plain");
}

void api_log(const Request& req, const Response&) {
	std::cout << req.method << " " << req.path << "\n";
}
