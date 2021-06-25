#include "httplib.h"

int main() {
	httplib::Server server;

	server.Get("/", [](const auto&, auto &res) {
		res.set_content("Hello!", "text/plain");
	});

	server.set_logger([](const auto& req, const auto& _) {
		(void)_;

		std::cout << req.method << " " << req.path << "\n";
	});

	std::cout << "Starting...\n";
	server.listen("0.0.0.0", 8080);
}
