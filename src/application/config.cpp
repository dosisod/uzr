#include <string>

#include "./config.hpp"

constexpr int DEFAULT_PORT = 8080;
constexpr const char* DEFAULT_HOST = "0.0.0.0";

static int getPortOrDefault() {
	auto *port = std::getenv("UZR_PORT");

	return port ? std::stoi(port) : DEFAULT_PORT;
}

static const char* getHostOrDefault() {
	auto *host = std::getenv("UZR_HOST");

	return host ? host : DEFAULT_HOST;
}

ApplicationConfig::ApplicationConfig() :
	port(getPortOrDefault()),
	host(getHostOrDefault())
	{}
