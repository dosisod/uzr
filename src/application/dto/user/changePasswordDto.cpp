#include "changePasswordDto.hpp"

ChangePasswordDto ChangePasswordDto::fromJson(const JsonBody& parsed) {
	ChangePasswordDto dto = {{
		.userId = UUID(parsed.value("userId", "")),
		.newPassword = parsed.value("newPassword", ""),
	}};

	dto.validate();

	return dto;
}

ChangePasswordDto::ChangePasswordDto(const ChangePassword& pwd) :
	ChangePassword(pwd) {}
