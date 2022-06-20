#include <algorithm>

#include <SQLiteCpp/Statement.h>
#include <base64.hpp>

#include "application/error.hpp"

#include "./userRepo.hpp"

static char hexToBinary(char c);

UserRepo::UserRepo(const InfrastructureConfig& config) :
	db(config.dbFilename, SQLite::OPEN_READWRITE) {}

void UserRepo::addUser(NewUserInfo user) {
	if (getByUsername(user.username)) {
		throw BadRequestException("Username is already taken");
	}

	UUID id = UUID();
	auto *hash = crypt(
		user.password.c_str(),
		("$6$" + uuidToCryptSalt(id)).c_str()
	);

	SQLite::Statement query(db, "INSERT INTO users VALUES (?, ?, ?)");
	query.bind(1, (std::string)id);
	query.bind(2, user.username);
	query.bind(3, hash);

	query.exec();
}

bool UserRepo::isValidLogin(Login login) {
	SQLite::Statement query(db, "SELECT password_hash FROM users WHERE username = ?");
	query.bind(1, login.username);

	if (!query.executeStep()) return false;

	std::string hash = query.getColumn(0);

	return strcmp(
		hash.c_str(),
		crypt(login.password.c_str(), hash.c_str())
	) == 0;
}

std::optional<User> UserRepo::getByUsername(std::string username) {
	SQLite::Statement query(db, "SELECT uuid, username FROM users WHERE username = ?");
	query.bind(1, username);

	if (!query.executeStep()) return {};

	return User {
		.id = UUID(query.getColumn(0)),
		.username = query.getColumn(1)
	};
}

static char hexToBinary(char c) {
	switch (c) {
		default:
		case '0': return '\0';
		case '1': return '\x1';
		case '2': return '\x2';
		case '3': return '\x3';
		case '4': return '\x4';
		case '5': return '\x5';
		case '6': return '\x6';
		case '7': return '\x7';
		case '8': return '\x8';
		case '9': return '\x9';
		case 'A':
		case 'a': return '\xA';
		case 'B':
		case 'b': return '\xB';
		case 'C':
		case 'c': return '\xC';
		case 'D':
		case 'd': return '\xD';
		case 'E':
		case 'e': return '\xE';
		case 'F':
		case 'f': return '\xF';
	}
}

std::string uuidToCryptSalt(const UUID& uuid) {
	std::string hex = (std::string)uuid;
	hex.erase(std::remove(hex.begin(), hex.end(), '-'), hex.end());

	std::string binary(16, ' ');

	for (unsigned i = 0; i < hex.length(); i += 2) {
		const unsigned byte = (
			hexToBinary(hex[i]) << 4) |
			hexToBinary(hex[i + 1]
		);

		binary[i / 2] = (char)byte;
	}

	return Base64::Encode(binary);
}
