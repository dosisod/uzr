#include "application/dto/user/changePasswordDto.hpp"
#include "application/dto/user/newUserInfoDto.hpp"
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
		IUserRepo& repo = DiCreate<IUserRepo&>();

		repo.addUser(NewUserInfoDto::fromJson(req.body));

		res.status = 204;
	}

	void changePassword(const Request& req, Response& res) {
		IUserRepo& repo = DiCreate<IUserRepo&>();

		repo.changePassword(ChangePasswordDto::fromJson(req.body));

		res.status = 204;
	}

	void setup(Server& server) {
		server.Post("/auth/login", login);
		server.Post("/auth/addUser", addUser);
		server.Post("/auth/changePassword", changePassword);
	}
}
