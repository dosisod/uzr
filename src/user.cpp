#include <iostream>
#include <pwd.h>
#include <shadow.h>
#include <sstream>
#include <string.h>
#include <unistd.h>

#include <json.hpp>
using json = nlohmann::json;

#include "err.hpp"
#include "user.hpp"

std::string get_user_by_name(const char* username) {
	setpwent();
	auto entry = getpwnam(username);
	endpwent();

	if (!entry) return nullptr;

	json user = {
		{ "username", username },
		{ "userId", entry->pw_uid },
		{ "groupId", entry->pw_gid }
	};

	return user.dump();
}

std::string login(std::string body) {
	json login_req = json::parse(body);

	std::string password = login_req.value("password", "");
	std::string username = login_req.value("username", "");

	if (username.empty() || password.empty()) {
		throw BadRequestException("Username or password not set");
	}

	setspent();
	auto entry = getspnam(username.c_str());
	endspent();

	const char* login_fail_msg = "Invalid username or password";

	if (!entry)
		throw UnauthorizedException(login_fail_msg);

	if (strcmp(entry->sp_pwdp, crypt(password.c_str(), entry->sp_pwdp)) == 0) {
		return get_user_by_name(username.c_str());
	}

	throw UnauthorizedException(login_fail_msg);
}
