#pragma once

#include "domain/errors.hpp"

#include "domain/user.hpp"

struct NewUserInfo {
	std::string username;
	std::string password;
	std::string full_name;
	std::string phone_number;
	std::string email;

	void validate() const {
		if (username.empty())
			throw ValidationError("Username cannot be empty");
		if (password.empty())
			throw ValidationError("Password cannot be empty");
		if (full_name.empty())
			throw ValidationError("Name cannot be empty");
		if (phone_number.empty())
			throw ValidationError("Phone number cannot be empty");
		if (email.empty())
			throw ValidationError("Email cannot be empty");
	}
};

struct Login {
	std::string username;
	std::string password;

	void validate() const {
		if (username.empty() || password.empty()) {
			throw ValidationError("Username or password not set");
		}
	}
};

class IUserRepo {
public:
	virtual void addUser(NewUserInfo user) = 0;
	virtual bool isValidLogin(Login login) = 0;
	virtual std::optional<User> getByUsername(std::string username) = 0;

	virtual ~IUserRepo() {}
};
