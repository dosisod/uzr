#pragma once

#include <string>

#include "application/dto/jsonBody.hpp"
#include "domain/repo/userRepo.hpp"

struct NewUserInfoDto : NewUserInfo {
	static NewUserInfoDto fromJson(const JsonBody&);
};
