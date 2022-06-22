#include "health.hpp"

namespace route::health {
	void get(const Request&, Response& res) {
		res.set_content("ok", "text/plain");
	}

	void setup(Server& server) {
		server.Get("/health", get);
	}
}
