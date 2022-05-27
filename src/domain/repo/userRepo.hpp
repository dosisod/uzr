#pragma once

#include "../user.hpp"

struct UserDto {
	std::string username;
	std::string password;
	std::string full_name;
	std::string phone_number;
	std::string email;
};

struct LoginDto {
	std::string username;
	std::string password;
};

class IUserRepo {
public:
	virtual void addUser(UserDto user) = 0;
	virtual bool isValidLogin(LoginDto login) = 0;
	virtual std::optional<User> getByUsername(std::string username) = 0;

	virtual ~IUserRepo() {}
};
