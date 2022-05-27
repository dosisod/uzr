#pragma once

#include "httplib.h"

#include "config.hpp"

class App {
public:
	App(ApplicationConfig config);

	int serve();

private:
	ApplicationConfig config;
	httplib::Server server;
};
