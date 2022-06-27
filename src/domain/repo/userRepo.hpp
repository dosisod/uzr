#pragma once

#include <optional>

#include "common/metadata.hpp"
#include "domain/errors.hpp"

#include "domain/user.hpp"

struct NewUserInfo {
	std::string username;
	std::string password;
	std::optional<Metadata> metadata = {};

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

struct ChangePassword {
	UUID userId;
	std::string newPassword;

	void validate() const {
		if (!userId || newPassword.empty()) {
			throw ValidationError("User id or new password is empty");
		}
	}
};

class IUserRepo {
public:
	virtual void addUser(const NewUserInfo& user) = 0;
	virtual bool isValidLogin(const Login& login) = 0;
	virtual std::optional<User> getByUsername(const std::string& username) = 0;
	virtual void changePassword(const ChangePassword& req) = 0;

	virtual ~IUserRepo() = default;
};
