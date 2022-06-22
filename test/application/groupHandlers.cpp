#include <utility>

#include "catch.hpp"

#include "application/error.hpp"
#include "application/handlers/group/getGroupByIdQueryHandler.hpp"
#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"

class FakeRepo : public IGroupRepo {
public:
	explicit FakeRepo(Group g) : group(std::move(g)) {}

	std::optional<Group> getGroupById(const UUID&) override {
		return group;
	}

	std::optional<Group> addGroup(const NewGroup&) override { return {}; }

private:
	Group group;
};

class DummyRepo : public IGroupRepo {
public:
	std::optional<Group> getGroupById(const UUID&) override {
		return {};
	}

	std::optional<Group> addGroup(const NewGroup&) override { return {}; }
};

TEST_CASE("Group not found throws exception") {
	auto repo = DummyRepo();
	auto query = GetGroupByIdQueryHandler(repo);
	auto invalidUuid = UUID();

	REQUIRE_THROWS_AS(query.handle(invalidUuid), NotFoundException);
}

TEST_CASE("Group DTO returned when found") {
	auto validUuid = UUID();

	Group group = {
		.id = validUuid,
		.name = "root"
	};

	auto repo = FakeRepo(group);
	auto query = GetGroupByIdQueryHandler(repo);

	auto dto = query.handle(validUuid);

	CHECK(dto.id == validUuid);
	CHECK(dto.name == "root");
	CHECK_FALSE(((std::string)dto).empty());
}
