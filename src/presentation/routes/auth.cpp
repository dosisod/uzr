#include "application/handlers/user.hpp"
#include "infrastructure/repo/userRepo.hpp"

#include "auth.hpp"

namespace route::auth {
	void login(const Request& req, Response& res) {
		auto repo = UserRepo();
		auto resp = loginCommand(repo, LoginDto::fromJson(req.body));

		res.set_content(resp, "text/json");
	}

	void addUser(const Request& req, Response& res) {
		auto repo = UserRepo();

		addUserCommand(repo, NewUserInfoDto::fromJson(req.body));

		res.status = 204;
	}
}
