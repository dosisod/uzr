#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "application/error.hpp"
#include "infrastructure/repo/groupRepo.hpp"

#include "group.hpp"

std::string getGroupByIdQuery(IGroupRepo& groupRepo, unsigned gid) {
	auto group = groupRepo.getGroupById(gid);
	if (!group) throw NotFoundException();

	return (json {
		{ "id", group->id },
		{ "name", group->name },
		{ "members", group->users }
	}).dump();
}
