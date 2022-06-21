#include <json.hpp>
using json = nlohmann::json;


#include "./userDto.hpp"

UserDto::operator std::string() const {
	return (json {
		{ "username", username },
		{ "id", (std::string)id },
		{ "metadata", metadata },
	}).dump();
}

UserDto::UserDto(const User& u) : User(u) {}
