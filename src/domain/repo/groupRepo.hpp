#pragma once

#include <optional>

#include "../group.hpp"
#include "common/uuid.hpp"

class IGroupRepo {
public:
	virtual std::optional<Group> getGroupById(const UUID&) = 0;

	virtual ~IGroupRepo() = default;
};
