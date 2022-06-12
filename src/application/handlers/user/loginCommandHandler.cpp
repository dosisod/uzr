#include "application/error.hpp"

#include "./loginCommandHandler.hpp"

LoginCommandHandler::LoginCommandHandler(IUserRepo &repo) : repo(repo) {}

UserDto LoginCommandHandler::handle(const LoginDto& login) {
	if (!repo.isValidLogin(login)) {
		throw UnauthorizedException("Invalid username or password");
	}

	auto user = repo.getByUsername(login.username);
	if (!user) throw ServerErrorException("Login succeeded but user not found");

	return {user.value()};
}
