#include <iostream>
#include <pwd.h>
#include <shadow.h>
#include <sstream>
#include <string.h>
#include <unistd.h>

#include "user.hpp"

std::string get_user_by_name(std::string username) {
	setpwent();
	auto entry = getpwnam(username.c_str());
	endpwent();

	if (!entry) return nullptr;

	std::ostringstream user;

	user << "{" <<
		"\"username\":\"" << username << "\"," <<
		"\"userId\":" << entry->pw_uid << "," <<
		"\"groupId\":" << entry->pw_gid <<
	"}";

	return user.str();
}

std::string login(std::string username, std::string password) {
	setspent();
	auto entry = getspnam(username.c_str());
	endspent();

	if (!entry) return "";

	if (strcmp(entry->sp_pwdp, crypt(password.c_str(), entry->sp_pwdp)) == 0) {
		return get_user_by_name(username);
	}

	return "";
}
