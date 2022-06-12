#include <json.hpp>
using json = nlohmann::json;


#include "./newUserInfoDto.hpp"

NewUserInfoDto NewUserInfoDto::fromJson(const std::string& jsonBody) {
	auto parsed = json::parse(jsonBody);

	NewUserInfoDto newUser = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", ""),
		.full_name = parsed.value("fullName", ""),
		.phone_number = parsed.value("phoneNumber", ""),
		.email = parsed.value("email", "")
	}};

	newUser.validate();

	return newUser;
}
