#include "application/handlers/user/addUserCommandHandler.hpp"
#include "application/handlers/user/loginCommandHandler.hpp"
#include "domain/repo/userRepo.hpp"
#include "presentation/di.hpp"

#include "auth.hpp"

namespace route::auth {
	void login(const Request& req, Response& res) {
		auto cmd = DiCreate<LoginCommandHandler>();
		auto resp = cmd.handle(LoginDto::fromJson(req.body));

		res.set_content(resp, "text/json");
	}

	void addUser(const Request& req, Response& res) {
		auto cmd = DiCreate<AddUserCommandHandler>();

		cmd.handle(NewUserInfoDto::fromJson(req.body));

		res.status = 204;
	}

	void setup(Server& server) {
		server.Post("/auth/login", login);
		server.Post("/auth/addUser", addUser);
	}
}
