#pragma once

#include <grp.h>

#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"

class GroupRepo : public IGroupRepo {
public:
	std::optional<Group> getGroupById(unsigned gid) override {
		setgrent();
		auto *entry = getgrgid(gid);
		endgrent();

		if (!entry) return {};

		std::vector<std::string> members = {};

		while (*entry->gr_mem) {
			members.emplace_back(*entry->gr_mem);
			entry->gr_mem++; // NOLINT
		}

		return Group {
			.id = gid,
			.name = entry->gr_name,
			.users = members,
		};
	}
};
