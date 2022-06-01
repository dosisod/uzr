#include <utility>

#include "catch.hpp"

#include "application/error.hpp"
#include "application/handlers/group.hpp"
#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"

class FakeRepo : public IGroupRepo {
public:
	explicit FakeRepo(Group g) : group(std::move(g)) {}

	std::optional<Group> getGroupById(unsigned) override {
		return group;
	}

private:
	Group group;
};

class DummyRepo : public IGroupRepo {
public:
	std::optional<Group> getGroupById(unsigned) override {
		return {};
	}
};

TEST_CASE("Group not found throws exception") {
	auto repo = DummyRepo();

	REQUIRE_THROWS_AS(getGroupByIdQuery(repo, 0), NotFoundException);
}

TEST_CASE("Group DTO returned when found") {
	Group group = {
		.id = 0,
		.name = "root",
		.users = {}
	};

	auto repo = FakeRepo(group);
	auto dto = getGroupByIdQuery(repo, 0);

	CHECK(dto.id == 0);
	CHECK(dto.name == "root");
	CHECK(dto.users.empty());
	CHECK_FALSE(((std::string)dto).empty());
}
