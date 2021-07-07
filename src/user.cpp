#include <errno.h>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <sys/wait.h>
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

std::string add_user(std::string body) {
	json new_user = json::parse(body);

	std::string username = new_user.value("username", "");
	std::string password = new_user.value("password", "");
	std::string gecos = new_user.value("gecos", "");

	if (username.empty())
		throw BadRequestException("Username cannot be empty");
	if (password.empty())
		throw BadRequestException("Password cannot be empty");
	if (gecos.empty())
		throw BadRequestException("Gecos cannot be empty");

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
			gecos.c_str(),
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

	return "ok";
}
