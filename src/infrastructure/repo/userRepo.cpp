#include <algorithm>
#include <crypt.h>

#include <SQLiteCpp/Statement.h>
#include <json.hpp>
using json = nlohmann::json;

#include "application/error.hpp"

#include "./userRepo.hpp"

static const char* getCryptHash(const std::string& password);

UserRepo::UserRepo(const InfrastructureConfig& config) :
	db(config.dbFilename, SQLite::OPEN_READWRITE) {}

void UserRepo::addUser(const NewUserInfo& user) {
	if (getByUsername(user.username)) {
		throw BadRequestException("Username is already taken");
	}

	auto id = (std::string)UUID();
	const auto *hash = getCryptHash(user.password);
	auto metadata = json(user.metadata.value_or(Metadata{})).dump();

	SQLite::Statement query(db, "INSERT INTO users VALUES (?, ?, ?, ?)");
	query.bind(1, id);
	query.bind(2, user.username);
	query.bind(3, hash);
	query.bind(4, metadata);

	query.exec();
}

bool UserRepo::isValidLogin(const Login& login) {
	SQLite::Statement query(db, "SELECT password_hash FROM users WHERE username = ?");
	query.bind(1, login.username);

	if (!query.executeStep()) return false;

	std::string hash = query.getColumn(0);

	return strcmp(
		hash.c_str(),
		crypt(login.password.c_str(), hash.c_str())
	) == 0;
}

std::optional<User> UserRepo::getByUsername(const std::string& username) {
	SQLite::Statement query(db, "SELECT uuid, username, metadata FROM users WHERE username = ?");
	query.bind(1, username);

	if (!query.executeStep()) return {};

	return User {
		.id = UUID(query.getColumn(0)),
		.username = query.getColumn(1),
		.metadata = json::parse((std::string)query.getColumn(2)).get<Metadata>()
	};
}

void UserRepo::changePassword(const ChangePassword& req) {
	SQLite::Statement query(db, "UPDATE users SET password_hash = ? WHERE uuid = ?");
	query.bind(1, getCryptHash(req.newPassword));
	query.bind(2, (std::string)req.userId);

	query.exec();
}

static const char* getCryptHash(const std::string& password) {
	auto *salt = crypt_gensalt("$6$", 10'000, nullptr, 0);
	return crypt(password.c_str(), salt);
}
