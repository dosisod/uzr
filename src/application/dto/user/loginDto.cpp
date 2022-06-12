#include <json.hpp>
using json = nlohmann::json;


#include "./loginDto.hpp"

LoginDto LoginDto::fromJson(const std::string& jsonBody) {
	// TODO(dosisod): create "JsonBody" type to auto-convert/parse json string
	auto parsed = json::parse(jsonBody);

	LoginDto login = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", "")
	}};

	login.validate();

	return login;
}
