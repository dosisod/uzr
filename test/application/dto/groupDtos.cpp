#include "catch.hpp"

#include "application/dto/group/groupDto.hpp"
#include "application/dto/group/newGroupDto.hpp"
#include "common/uuid.hpp"

TEST_CASE("Create and stringify GroupDto") {
	UUID id("5f233938-8fcc-47ec-9a06-a11169819aee");

	auto dto = GroupDto(Group {
		.id = id,
		.name = "group name",
		.metadata = {{"key", "value"}}
	});

	const auto* expected = R"({"id":"5f233938-8fcc-47ec-9a06-a11169819aee","metadata":{"key":"value"},"name":"group name"})";

	CHECK((std::string)dto == expected);
}

TEST_CASE("Create NewGroupDto from JSON") {
	std::string jsonBody = R"({"name":"some group","metadata":{"key":"value"}})";

	auto newGroup = NewGroupDto::fromJson(jsonBody);

	CHECK(newGroup.name == "some group");
	REQUIRE(newGroup.metadata.has_value());
	CHECK((*newGroup.metadata)["key"] == "value");
}
