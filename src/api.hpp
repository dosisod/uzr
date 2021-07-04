#pragma once

#include "httplib.h"

using namespace httplib;

void api_health(const Request&, Response&);
void api_login(const Request&, Response&);
void api_get_group_by_id(const Request&, Response&);
void api_log(const Request&, const Response&);
void api_handle_exception(const Request&, Response&, std::exception&);
