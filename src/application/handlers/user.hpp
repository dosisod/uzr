#pragma once

#include <string>

#include "infrastructure/repo/userRepo.hpp"

struct UserDto : User {
	operator std::string() const;

	UserDto(const User& u);
};

struct LoginDto : Login {
	static LoginDto fromJson(const std::string& jsonBody);
};

struct NewUserInfoDto : NewUserInfo {
	static NewUserInfoDto fromJson(const std::string& jsonBody);
};

UserDto loginCommand(IUserRepo&, const LoginDto&);
void addUserCommand(IUserRepo&, NewUserInfoDto);
