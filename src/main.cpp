#include <cstdlib>
#include <string>

#include "httplib.h"

#include "api.hpp"

#define DEFAULT_PORT 8080
#define DEFAULT_HOST "0.0.0.0"

int main() {
	const auto uzr_port = std::getenv("UZR_PORT");
	const int port = uzr_port ? std::stoi(uzr_port) : DEFAULT_PORT;

	const auto uzr_host = std::getenv("UZR_HOST");
	const char *host = uzr_host ? uzr_host : DEFAULT_HOST;

	std::cout << "Starting on " << host << ":" << port << "\n";

	httplib::Server server;

	server.Get("/health", api_health);
	server.Post("/login", api_login);
	server.Post("/user/add", api_add_user);
	server.Get("/group/(\\d+)", api_get_group_by_id);
	server.set_logger(api_log);
	server.set_exception_handler(api_handle_exception);

	errno = 1;
	server.listen(host, port);
	perror("uzr");

	return 1;
}
