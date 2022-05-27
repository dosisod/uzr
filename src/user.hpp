#pragma once

#include <string>

#include "domain/repo/userRepo.hpp"

std::string loginCommand(IUserRepo&, std::string);
std::string addUserCommand(IUserRepo&, std::string);
