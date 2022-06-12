#pragma once

#include "application/dto/user/userDto.hpp"
#include "application/dto/user/loginDto.hpp"

class LoginCommandHandler {
public:
	LoginCommandHandler(IUserRepo&);

	UserDto handle(const LoginDto& login);

private:
	IUserRepo& repo;
};
