#include <iostream>

#include "httplib.h"

#include "user.hpp"

using namespace httplib;

void api_health(const Request&, Response& res) {
	res.set_content("ok", "text/plain");
}

void api_login(const Request& req, Response& res) {
	auto user = login(req.matches[1], req.matches[2]);

	res.status = user.empty() ? 401 : 200;
	res.set_content(user.empty() ? "{}" : user, "text/plain");
}

void api_log(const Request& req, const Response&) {
	std::cout << req.method << " " << req.path << "\n";
}
