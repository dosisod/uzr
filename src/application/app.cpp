#include "json.hpp"
using json_exception = nlohmann::detail::exception;

#include "domain/errors.hpp"
#include "error.hpp"
#include "routes.hpp"

#include "app.hpp"

static void logger(const Request& req, const Response& res);
static void exceptionHandler(const Request&, Response& res, std::exception&);

App::App(ApplicationConfig config) : config(config) {
	std::cout << "Starting on " << config.host << ":" << config.port << "\n";

	server.Get("/health", route::health::get);
	server.Post("/auth/login", route::auth::login);
	server.Post("/auth/addUser", route::auth::addUser);
	server.Get("/group/(\\d+)", route::group::getById);
	server.set_logger(logger);
	server.set_exception_handler(exceptionHandler);
}

int App::serve() {
	errno = 1;
	server.listen(config.host, config.port);
	perror("uzr");

	return 1;
}

// TODO(dosisod): allow for optionally colorizing output
static void logger(const Request& req, const Response& res) {
	std::cout << req.method << " " << req.path << " " << res.status << std::endl;
}

static void exceptionHandler(const Request&, Response& res, std::exception&) {
	res.status = 500;

	try {
		std::rethrow_exception(std::current_exception());
	}
	catch (HttpException& e) {
		res.status = e.status;
		res.set_content(e.what(), "text/plain");
	}
	catch (json_exception &e) {
		res.status = 400;
		res.set_content(e.what(), "text/plain");
	}
	catch (ValidationError &e) {
		res.status = 400;
		res.set_content(e.what(), "text/plain");
	}
	catch (std::exception& e) {
		res.set_content(e.what(), "text/plain");
	}
}
