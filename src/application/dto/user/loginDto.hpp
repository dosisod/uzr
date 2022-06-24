#pragma once

#include <string>

#include "application/dto/jsonBody.hpp"
#include "domain/repo/userRepo.hpp"

struct LoginDto : Login {
	static LoginDto fromJson(const JsonBody&);

	LoginDto(const Login& l);
};
