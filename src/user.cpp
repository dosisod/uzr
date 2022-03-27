#include <errno.h>
#include <optional>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <json.hpp>
using json = nlohmann::json;

#include "err.hpp"
#include "user.hpp"

struct User {
	std::string username;
	unsigned long id;
	unsigned long groupId;
};

static std::optional<User> db_get_user_by_name(std::string username);
static bool db_username_validate_password(std::string username, std::string password);
static void db_add_user(
	std::string username,
	std::string password,
	std::string full_name,
	std::string phone_number,
	std::string email
);

std::string get_user_by_name(std::string username) {
	auto user = db_get_user_by_name(username);
	if (!user) return nullptr;

	return (json {
		{ "username", user->username },
		{ "userId", user->id },
		{ "groupId", user->groupId }
	}).dump();
}

std::string login(std::string body) {
	json login_req = json::parse(body);

	std::string password = login_req.value("password", "");
	std::string username = login_req.value("username", "");

	if (username.empty() || password.empty()) {
		throw BadRequestException("Username or password not set");
	}

	if (!db_username_validate_password(username.c_str(), password.c_str())) {
		throw UnauthorizedException("Invalid username or password");
	}

	return get_user_by_name(username.c_str());
}

std::string add_user(std::string body) {
	json new_user = json::parse(body);

	std::string username = new_user.value("username", "");
	std::string password = new_user.value("password", "");
	std::string full_name = new_user.value("fullName", "");
	std::string phone_number = new_user.value("phoneNumber", "");
	std::string email = new_user.value("email", "");

	if (username.empty())
		throw BadRequestException("Username cannot be empty");
	if (password.empty())
		throw BadRequestException("Password cannot be empty");
	if (full_name.empty())
		throw BadRequestException("Name cannot be empty");
	if (phone_number.empty())
		throw BadRequestException("Phone number cannot be empty");
	if (email.empty())
		throw BadRequestException("Email cannot be empty");

	db_add_user(username, password, full_name, phone_number, email);

	return "ok";
}

static std::optional<User> db_get_user_by_name(std::string username) {
	setpwent();
	auto entry = getpwnam(username.c_str());
	endpwent();

	if (!entry) return {};

	return User {
		.username = username,
		.id = entry->pw_uid,
		.groupId = entry->pw_gid
	};
}

static bool db_username_validate_password(std::string username, std::string password) {
	setspent();
	auto entry = getspnam(username.c_str());
	endspent();

	if (!entry) return false;

	return strcmp(entry->sp_pwdp, crypt(password.c_str(), entry->sp_pwdp)) == 0;
}

static void db_add_user(
	std::string username,
	std::string password,
	std::string full_name,
	std::string phone_number,
	std::string email
) {
	errno = 0;
	auto pid = fork();
	if (pid == -1) {
		perror("fork");
		throw ServerErrorException();
	}
	if (pid == 0) {
		errno = 0;
		execlp(
			"/app/scripts/user_add.sh",
			"/app/scripts/user_add.sh",
			username.c_str(),
			password.c_str(),
			(full_name + ",," + phone_number + ",," + email).c_str(),
			(char *)0
		);

		if (errno) {
			perror("execlp");
			throw ServerErrorException();
		}
	}

	int status = 0;
	waitpid(pid, &status, 0);

	if (WEXITSTATUS(status) != 1) {
		throw BadRequestException("Username is already taken");
	}
}
