#include "catch.hpp"

#include "common/uuid.hpp"
#include "infrastructure/config.hpp"
#include "infrastructure/repo/groupRepo.hpp"
#include "temporaryDb.hpp"

TEST_CASE("groups can be added and retrieved") {
	TemporaryDb db;
	InfrastructureConfig config;
	config.dbFilename = db.filename;

	GroupRepo repo(config);

	NewGroup newGroup {
		.name = "group name",
		.metadata = Metadata{{"key", "value"}}
	};

	auto addedGroup = repo.addGroup(newGroup);

	REQUIRE(addedGroup.has_value());
	REQUIRE(addedGroup->id);
	REQUIRE(addedGroup->name == "group name");
	REQUIRE(addedGroup->metadata["key"] == "value");

	auto foundGroup = repo.getGroupById(addedGroup->id);
	REQUIRE(foundGroup.has_value());
	REQUIRE(foundGroup->id == addedGroup->id);
}
