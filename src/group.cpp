#include <grp.h>
#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

#include "err.hpp"
#include "group.hpp"

std::string get_group_by_id(unsigned gid) {
	setgrent();
	auto entry = getgrgid(gid);
	endgrent();

	if (!entry) throw NotFoundException();

	json group = {
		{ "id", gid },
		{ "name", entry->gr_name },
		{ "members", nullptr }
	};

	while (*entry->gr_mem) {
		group["members"].emplace_back(*entry->gr_mem);
		entry->gr_mem++;
	}

	return group.dump();
}
