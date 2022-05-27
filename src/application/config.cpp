#include "./config.hpp"

#define DEFAULT_PORT 8080
#define DEFAULT_HOST "0.0.0.0"

static int getPortOrDefault() {
	const auto port = std::getenv("UZR_PORT");

	return port ? std::stoi(port) : DEFAULT_PORT;
}

static const char* getHostOrDefault() {
	const auto host = std::getenv("UZR_HOST");

	return host ? host : DEFAULT_HOST;
}

ApplicationConfig::ApplicationConfig() :
	port(getPortOrDefault()),
	host(getHostOrDefault())
	{}
