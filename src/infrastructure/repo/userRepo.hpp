#pragma once

#include <cerrno>
#include <pwd.h>
#include <shadow.h>
#include <string>
#include <string.h> // NOLINT
#include <sys/wait.h>
#include <unistd.h>

#include "application/error.hpp"
#include "domain/repo/userRepo.hpp"

// TODO(dosisod): should be defined in src/infrastructre
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SCRIPT_DIR "/app/src/scripts"

class UserRepo : public IUserRepo {
public:
	void addUser(NewUserInfo user) override {
		// TODO(dosisod): create a wrapper for calling shell scripts
		errno = 0;
		auto pid = fork();
		if (pid == -1) {
			perror("fork");
			throw ServerErrorException();
		}
		if (pid == 0) {
			errno = 0;
			execlp( // NOLINT
				SCRIPT_DIR"/user_add.sh",
				SCRIPT_DIR"/user_add.sh",
				user.username.c_str(),
				user.password.c_str(),
				(user.full_name + ",," + user.phone_number + ",," + user.email).c_str(),
				nullptr
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

	bool isValidLogin(Login login) override {
		setspent();
		auto *entry = getspnam(login.username.c_str());
		endspent();

		if (!entry) return false;

		return strcmp(
			entry->sp_pwdp,
			crypt(login.password.c_str(), entry->sp_pwdp)
		) == 0;
	}

	std::optional<User> getByUsername(std::string username) override {
		setpwent();
		auto *entry = getpwnam(username.c_str());
		endpwent();

		if (!entry) return {};

		return User {
			.username = username,
			.id = entry->pw_uid,
			.groupId = entry->pw_gid
		};
	}
};

