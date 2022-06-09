#pragma once

#include <string>

#include "domain/repo/userRepo.hpp"

struct NewUserInfoDto : NewUserInfo {
	static NewUserInfoDto fromJson(const std::string& jsonBody);
};
