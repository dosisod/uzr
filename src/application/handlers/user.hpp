#pragma once

#include <string>

#include "infrastructure/repo/userRepo.hpp"

struct UserDto : User {
	operator std::string() const;
};

struct LoginDto : Login {
	static LoginDto fromJson(std::string jsonBody);
};

struct NewUserInfoDto : NewUserInfo {
	static NewUserInfoDto fromJson(std::string jsonBody);
};

UserDto loginCommand(IUserRepo&, LoginDto);
void addUserCommand(IUserRepo&, NewUserInfoDto);
