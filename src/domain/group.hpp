#pragma once

#include <string>
#include <vector>

#include "common/metadata.hpp"
#include "common/uuid.hpp"

struct Group {
	UUID id;
	std::string name;
	Metadata metadata = {};
};
