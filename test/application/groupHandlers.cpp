#include "catch.hpp"

#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"
#include "application/error.hpp"
#include "application/handlers/group.hpp"

class FakeRepo : public IGroupRepo {
public:
	FakeRepo(Group g) : group(g) {}

	virtual std::optional<Group> getGroupById(unsigned) {
		return group;
	}

private:
	Group group;
};

class DummyRepo : public IGroupRepo {
public:
	virtual std::optional<Group> getGroupById(unsigned) {
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
	CHECK(dto.users.size() == 0);
	CHECK_FALSE(((std::string)dto).empty());
}
