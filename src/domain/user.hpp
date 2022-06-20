#pragma once

#include <string>

#include "common/uuid.hpp"

struct User {
	UUID id;
	std::string username;
};
