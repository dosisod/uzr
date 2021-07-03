#include <iostream>

#include "httplib.h"

#include "err.hpp"
#include "user.hpp"

using namespace httplib;

void api_health(const Request&, Response& res) {
	res.set_content("ok", "text/plain");
}

void api_login(const Request& req, Response& res) {
	res.set_content(login(req.body), "text/plain");
}

void api_log(const Request& req, const Response& res) {
	std::cout << req.method << " " << req.path << " " << res.status << std::endl;
}

void api_handle_exception(const Request&, Response& res, std::exception&) {
	res.status = 500;

	try {
		std::rethrow_exception(std::current_exception());
	}
	catch (HttpException& e) {
		res.status = e.status;
		res.set_content(e.what(), "text/plain");
	}
	catch (std::exception& e) {
		res.set_content(e.what(), "text/plain");
	}
}
