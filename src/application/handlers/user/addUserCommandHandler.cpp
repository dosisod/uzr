#include "./addUserCommandHandler.hpp"

AddUserCommandHandler::AddUserCommandHandler(IUserRepo& repo) : repo(repo) {}

void AddUserCommandHandler::handle(const NewUserInfoDto& newUser) {
	repo.addUser(newUser);
}
