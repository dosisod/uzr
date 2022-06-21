#pragma once

#include <string>

#include "common/metadata.hpp"
#include "common/uuid.hpp"

struct User {
	UUID id;
	std::string username;
	Metadata metadata = {};
};
