#pragma once

#include <grp.h>

#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"

class GroupRepo : public IGroupRepo {
public:
	virtual std::optional<Group> getGroupById(unsigned gid) {
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
};
