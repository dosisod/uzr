#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "application/error.hpp"
#include "domain/user.hpp"
#include "infrastructure/repo/userRepo.hpp"

#include "user.hpp"

UserDto loginCommand(IUserRepo& userRepo, LoginDto login) {
	if (!userRepo.isValidLogin(login)) {
		throw UnauthorizedException("Invalid username or password");
	}

	auto user = userRepo.getByUsername(login.username);
	if (!user) throw ServerErrorException("Login succeeded but user not found");

	return UserDto(user.value());
}

void addUserCommand(IUserRepo& userRepo, NewUserInfoDto newUser) {
	userRepo.addUser(newUser);
}

UserDto::operator std::string() const {
	return (json {
		{ "username", username },
		{ "userId", id },
		{ "groupId", groupId }
	}).dump();
}

LoginDto LoginDto::fromJson(std::string jsonBody) {
	// TODO: create "JsonBody" type to auto-convert/parse json string
	auto parsed = json::parse(jsonBody);

	LoginDto login = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", "")
	}};

	login.validate();

	return login;
}

NewUserInfoDto NewUserInfoDto::fromJson(std::string jsonBody) {
	auto parsed = json::parse(jsonBody);

	NewUserInfoDto newUser = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", ""),
		.full_name = parsed.value("fullName", ""),
		.phone_number = parsed.value("phoneNumber", ""),
		.email = parsed.value("email", "")
	}};

	newUser.validate();

	return newUser;
}
