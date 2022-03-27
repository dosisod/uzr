#include <grp.h>
#include <optional>
#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "err.hpp"
#include "group.hpp"

struct Group {
	unsigned long id;
	std::string name;
	std::vector<std::string> users;
};

static std::optional<Group> db_get_group_by_id(unsigned gid);

std::string get_group_by_id(unsigned gid) {
	auto group = db_get_group_by_id(gid);
	if (!group) throw NotFoundException();

	return (json {
		{ "id", group->id },
		{ "name", group->name },
		{ "members", group->users }
	}).dump();
}

static std::optional<Group> db_get_group_by_id(unsigned gid) {
	setgrent();
	auto entry = getgrgid(gid);
	endgrent();

	if (!entry) return {};

	std::vector<std::string> members = {};

	while (*entry->gr_mem) {
		members.emplace_back(*entry->gr_mem);
		entry->gr_mem++;
	}

	return Group {
		.id = gid,
		.name = entry->gr_name,
		.users = members,
	};
}
