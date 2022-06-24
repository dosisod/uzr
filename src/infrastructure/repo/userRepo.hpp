#pragma once

#include <string>

#include <SQLiteCpp/Database.h>

#include "domain/repo/userRepo.hpp"
#include "infrastructure/config.hpp"

// For crypt() to be safe, we need to use a salt. We will use the user UUID
// as the salt value, though we have to convert it to a safe version (also,
// the UUID will most likely be truncated, which is not good for security).
// We convert the hex UUID to binary, then to base64, to provide the most
// feasibly dense salt that we can.
std::string uuidToCryptSalt(const UUID& uuid);

class UserRepo : public IUserRepo {
public:
	UserRepo(const InfrastructureConfig& config);

	void addUser(const NewUserInfo& user) override;
	bool isValidLogin(const Login& login) override;
	std::optional<User> getByUsername(const std::string& username) override;

private:
	SQLite::Database db;
};
