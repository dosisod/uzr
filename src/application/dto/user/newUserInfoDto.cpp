#include <json.hpp>
using json = nlohmann::json;


#include "./newUserInfoDto.hpp"

NewUserInfoDto NewUserInfoDto::fromJson(const std::string& jsonBody) {
	auto parsed = json::parse(jsonBody);

	NewUserInfoDto newUser = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", "")
	}};

	newUser.validate();

	return newUser;
}
