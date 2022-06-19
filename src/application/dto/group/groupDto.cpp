#include <json.hpp>
using json = nlohmann::json;

#include "common/uuid.hpp"

#include "./groupDto.hpp"

GroupDto::operator std::string() const {
	return (json {
		{ "id", (std::string)this->id },
		{ "name", this->name }
	}).dump();
}

GroupDto::GroupDto(const Group& g) : Group(g) {}
