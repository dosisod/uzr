#include "httplib.h"

using namespace httplib;

namespace route::auth {
	void login(const Request& req, Response& res);
	void addUser(const Request& req, Response& res);
}
