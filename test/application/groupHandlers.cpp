#include <utility>

#include "catch.hpp"
#include "fakeit.hpp"
using namespace fakeit;

#include "application/error.hpp"
#include "application/handlers/group/addGroupCommandHandler.hpp"
#include "application/handlers/group/getGroupByIdQueryHandler.hpp"
#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"


TEST_CASE("Group not found throws exception") {
	Mock<IGroupRepo> mock;
	Fake(Method(mock, getGroupById), Method(mock, addGroup));

	auto query = GetGroupByIdQueryHandler(mock.get());
	auto invalidUuid = UUID();

	REQUIRE_THROWS_AS(query.handle(invalidUuid), NotFoundException);

	Verify(Method(mock, getGroupById)).Once();
}

TEST_CASE("Group DTO returned when found") {
	auto validUuid = UUID();

	Group group = {
		.id = validUuid,
		.name = "root"
	};

	Mock<IGroupRepo> mock;
	When(Method(mock, getGroupById)).Return(group);

	auto query = GetGroupByIdQueryHandler(mock.get());

	auto dto = query.handle(validUuid);

	CHECK(dto.id == validUuid);
	CHECK(dto.name == "root");
	CHECK_FALSE(((std::string)dto).empty());

	Verify(Method(mock, getGroupById)).Once();
}

TEST_CASE("Add group") {
	Mock<IGroupRepo> mock;
	When(Method(mock, addGroup)).Do([](auto g){
		return Group {
			.id = UUID(),
			.name = g.name
		};
	});

	NewGroup group = { .name = "group name" };

	auto cmd = AddGroupCommandHandler(mock.get());
	auto addedGroup = cmd.handle(group);

	CHECK(addedGroup.id);
	CHECK(addedGroup.name == "group name");
}

TEST_CASE("Add group with same name fails") {
	Mock<IGroupRepo> mock;
	Fake(Method(mock, addGroup));

	NewGroup group = { .name = "group name" };
	auto cmd = AddGroupCommandHandler(mock.get());

	REQUIRE_THROWS_AS(cmd.handle(group), BadRequestException);

	Verify(Method(mock, addGroup)).Once();
}
