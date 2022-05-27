#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "infrastructure/repo/userRepo.hpp"

#include "application/error.hpp"
#include "domain/user.hpp"

std::string loginCommand(IUserRepo& userRepo, std::string body) {
	json parsed = json::parse(body);

	auto login = LoginDto {
		.username = parsed.value("username", ""),
		.password = parsed.value("password", "")
	};

	if (login.username.empty() || login.password.empty()) {
		throw BadRequestException("Username or password not set");
	}

	if (!userRepo.isValidLogin(login)) {
		throw UnauthorizedException("Invalid username or password");
	}

	auto user = userRepo.getByUsername(login.username);
	if (!user) return nullptr;

	// TODO: this should be its own function
	return (json {
		{ "username", user->username },
		{ "userId", user->id },
		{ "groupId", user->groupId }
	}).dump();
}

std::string addUserCommand(IUserRepo& userRepo, std::string body) {
	json parsed = json::parse(body);

	auto newUser = UserDto {
		.username = parsed.value("username", ""),
		.password = parsed.value("password", ""),
		.full_name = parsed.value("fullName", ""),
		.phone_number = parsed.value("phoneNumber", ""),
		.email = parsed.value("email", "")
	};

	if (newUser.username.empty())
		throw BadRequestException("Username cannot be empty");
	if (newUser.password.empty())
		throw BadRequestException("Password cannot be empty");
	if (newUser.full_name.empty())
		throw BadRequestException("Name cannot be empty");
	if (newUser.phone_number.empty())
		throw BadRequestException("Phone number cannot be empty");
	if (newUser.email.empty())
		throw BadRequestException("Email cannot be empty");

	userRepo.addUser(newUser);

	// TODO: probably should use http 204 instead of "ok" (or return user)
	return "ok";
}
