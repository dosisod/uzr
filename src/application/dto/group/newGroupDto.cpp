#include "./newGroupDto.hpp"

NewGroupDto NewGroupDto::fromJson(const JsonBody& parsed) {
	std::optional<Metadata> metadata = {};
	if (parsed.contains("metadata")) metadata = parsed["metadata"];

	NewGroupDto newGroup = {{
		.name = parsed.value("name", ""),
		.metadata = metadata,
	}};

	newGroup.validate();

	return newGroup;
}

NewGroupDto::NewGroupDto(const NewGroup& group) : NewGroup(group) {}
