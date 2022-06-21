#include <json.hpp>
using json = nlohmann::json;


#include "./newUserInfoDto.hpp"

NewUserInfoDto NewUserInfoDto::fromJson(const std::string& jsonBody) {
	auto parsed = json::parse(jsonBody);

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
