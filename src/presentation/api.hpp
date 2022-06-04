#pragma once

#include "httplib.h"

#include "config.hpp"

class Api {
public:
	Api(ApiConfig config);

	int serve();

private:
	ApiConfig config;
	httplib::Server server;
};
