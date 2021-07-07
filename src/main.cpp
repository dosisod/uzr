#include <cstdlib>
#include <string>

#include "httplib.h"

#include "api.hpp"

#define DEFAULT_PORT 8080

int main() {
	const auto UZR_PORT = std::getenv("UZR_PORT");
	const int PORT = UZR_PORT ?
		std::stoi(UZR_PORT) :
		DEFAULT_PORT;

	std::cout << "Starting on port " << PORT << "\n";

	httplib::Server server;

	server.Get("/health", api_health);
	server.Post("/login", api_login);
	server.Post("/user/add", api_add_user);
	server.Get("/group/(\\d+)", api_get_group_by_id);
	server.set_logger(api_log);
	server.set_exception_handler(api_handle_exception);

	server.listen("0.0.0.0", PORT);
	perror("uzr");

	return 1;
}
