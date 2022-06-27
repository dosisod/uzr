#pragma once

#include <string>

#include "domain/repo/userRepo.hpp"
#include "../jsonBody.hpp"

struct ChangePasswordDto : public ChangePassword {
	static ChangePasswordDto fromJson(const JsonBody& parsed);

	ChangePasswordDto(const ChangePassword &);
};
