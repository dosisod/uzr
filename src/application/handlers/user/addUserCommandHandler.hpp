#pragma once

#include "application/dto/user/newUserInfoDto.hpp"
#include "domain/repo/userRepo.hpp"
#include "domain/user.hpp"

class AddUserCommandHandler {
public:
	AddUserCommandHandler(IUserRepo&);

	void handle(const NewUserInfoDto& newUser);

private:
	IUserRepo& repo;
};
