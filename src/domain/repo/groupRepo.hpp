#pragma once

#include <optional>

#include "../group.hpp"

class IGroupRepo {
public:
	virtual std::optional<Group> getGroupById(unsigned gid) = 0;

	virtual ~IGroupRepo() = default;
};
