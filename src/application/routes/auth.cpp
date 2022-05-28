#include "application/handlers/user.hpp"
#include "infrastructure/repo/userRepo.hpp"

#include "auth.hpp"

namespace route::auth {
	void login(const Request& req, Response& res) {
		auto repo = UserRepo();

		res.set_content(loginCommand(repo, req.body), "text/plain");
	}

	void addUser(const Request& req, Response& res) {
		auto repo = UserRepo();

		addUserCommand(repo, req.body);

		res.status = 204;
	}
}
