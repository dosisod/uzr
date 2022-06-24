#include "./newUserInfoDto.hpp"

NewUserInfoDto NewUserInfoDto::fromJson(const JsonBody& parsed) {
	std::optional<Metadata> metadata = {};
	if (parsed.contains("metadata")) metadata = parsed["metadata"];

	NewUserInfoDto newUser = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", ""),
		.metadata = metadata,
	}};

	newUser.validate();

	return newUser;
}
