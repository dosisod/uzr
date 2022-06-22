#pragma once

#include <optional>

#include "common/metadata.hpp"
#include "common/uuid.hpp"
#include "domain/errors.hpp"

#include "../group.hpp"

struct NewGroup {
	std::string name;
	std::optional<Metadata> metadata = {};

	void validate() const {
		if (name.empty())
			throw ValidationError("Name cannot be empty");
	}
};

class IGroupRepo {
public:
	virtual std::optional<Group> getGroupById(const UUID&) = 0;

	virtual std::optional<Group> addGroup(const NewGroup&) = 0;

	virtual ~IGroupRepo() = default;
};
