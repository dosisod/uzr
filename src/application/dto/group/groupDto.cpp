#include <json.hpp>
using json = nlohmann::json;

#include "./groupDto.hpp"

GroupDto::operator std::string() const {
	return (json {
		{ "id", this->id },
		{ "name", this->name },
		{ "members", this->users }
	}).dump();
}

GroupDto::GroupDto(const Group& g) : Group(g) {}
