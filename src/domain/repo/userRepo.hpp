#pragma once

#include <crypt.h>
#include <optional>

#include "common/metadata.hpp"
#include "domain/errors.hpp"

#include "domain/user.hpp"

struct NewUserInfo {
	std::string username;
	std::string password;
	std::optional<Metadata> metadata;

	void validate() const {
		if (username.empty())
			throw ValidationError("Username cannot be empty");
		if (password.empty())
			throw ValidationError("Password cannot be empty");
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

	virtual ~IUserRepo() = default;
};
