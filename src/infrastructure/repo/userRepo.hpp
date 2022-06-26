#pragma once

#include <string>

#include <SQLiteCpp/Database.h>

#include "domain/repo/userRepo.hpp"
#include "infrastructure/config.hpp"

class UserRepo : public IUserRepo {
public:
	UserRepo(const InfrastructureConfig& config);

	void addUser(const NewUserInfo& user) override;
	bool isValidLogin(const Login& login) override;
	std::optional<User> getByUsername(const std::string& username) override;

private:
	SQLite::Database db;
};
