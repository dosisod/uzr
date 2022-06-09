#pragma once

#include <string>

#include "domain/group.hpp"

struct GroupDto : Group {
	operator std::string() const;

	GroupDto(const Group& g);
};
