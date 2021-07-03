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

	if (login_req.find("username") == login_req.end() ||
		login_req.find("password") == login_req.end()
	) {
		throw BadRequestException("Username or password not set");
	}

	const char* username = login_req["username"].get<std::string>().c_str();
	const char* password = login_req["password"].get<std::string>().c_str();

	setspent();
	auto entry = getspnam(username);
	endspent();

	const char* login_fail_msg = "Invalid username or password";

	if (!entry)
		throw UnauthorizedException(login_fail_msg);

	if (strcmp(entry->sp_pwdp, crypt(password, entry->sp_pwdp)) == 0) {
		return get_user_by_name(username);
	}

	throw UnauthorizedException(login_fail_msg);
}
