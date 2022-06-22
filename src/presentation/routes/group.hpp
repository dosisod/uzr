#include "httplib.h"
using namespace httplib;

namespace route::group {
	void getById(const Request& req, Response& res);
	void addGroup(const Request& req, Response& res);
}
