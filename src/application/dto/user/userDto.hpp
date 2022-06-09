#pragma once

#include <string>

#include "domain/user.hpp"

struct UserDto : User {
	operator std::string() const;

	UserDto(const User& u);
};
