#pragma once

#include <string>

#include "domain/repo/userRepo.hpp"

struct LoginDto : Login {
	static LoginDto fromJson(const std::string& jsonBody);
};
