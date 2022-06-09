#pragma once

#include "domain/repo/userRepo.hpp"

#include "../dto/user/loginDto.hpp"
#include "../dto/user/newUserInfoDto.hpp"
#include "../dto/user/userDto.hpp"

UserDto loginCommand(IUserRepo&, const LoginDto&);
void addUserCommand(IUserRepo&, const NewUserInfoDto&);
