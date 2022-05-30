#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "application/error.hpp"
#include "infrastructure/repo/groupRepo.hpp"

#include "group.hpp"

GroupDto getGroupByIdQuery(IGroupRepo& groupRepo, unsigned gid) {
	auto group = groupRepo.getGroupById(gid);
	if (!group) throw NotFoundException();

	return GroupDto(group.value());
}

GroupDto::operator std::string() const {
	return (json {
		{ "id", this->id },
		{ "name", this->name },
		{ "members", this->users }
	}).dump();
}
