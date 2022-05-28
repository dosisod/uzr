#pragma once

#include <string>

#include "infrastructure/repo/userRepo.hpp"

std::string loginCommand(IUserRepo&, std::string);
void addUserCommand(IUserRepo&, std::string);
