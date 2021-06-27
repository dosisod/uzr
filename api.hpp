#pragma once

#include "httplib.h"

using namespace httplib;

void api_health(const Request&, Response&);
void api_login(const Request&, Response&);
void api_get_user_by_name(const Request&, Response&);
void api_log(const Request&, const Response&);
