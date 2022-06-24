#include <json.hpp>
using json = nlohmann::json;

#include "./newGroupDto.hpp"

NewGroupDto NewGroupDto::fromJson(const std::string& jsonBody) {
	auto parsed = json::parse(jsonBody);

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
