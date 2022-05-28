#include "health.hpp"

void route::health::get(const Request&, Response& res) {
	res.set_content("ok", "text/plain");
}
