#include <unordered_set>

#include "catch.hpp"

#include "common/uuid.hpp"

TEST_CASE("Parse null UUID") {
	UUID u = UUID("00000000-0000-0000-0000-000000000000");

	REQUIRE_FALSE(u);
}

TEST_CASE("Invalid UUID returns null UUID") {
	UUID u = UUID("invalid");

	REQUIRE_FALSE(u);
}

TEST_CASE("Parse and compare UUID") {
	std::string uuidAsString = "01234567-0123-0123-0123-0123456789AB";

	UUID u = UUID(uuidAsString);

	REQUIRE(u);
	REQUIRE((std::string)u == uuidAsString);
}

TEST_CASE("UUID comparisons") {
	auto uuid1 = UUID("11111111-1111-1111-1111-111111111111");
	auto uuid2 = UUID("11111111-1111-1111-1111-111111111111");
	auto uuid3 = UUID("22222222-2222-2222-2222-222222222222");

	REQUIRE(uuid1);
	REQUIRE(uuid2);
	REQUIRE(uuid3);

	CHECK(uuid1 == uuid1);
	CHECK(uuid2 == uuid2);
	CHECK(uuid3 == uuid3);

	CHECK(uuid1 == uuid2);
	CHECK(uuid2 == uuid1);

	CHECK(uuid1 != uuid3);
	CHECK(uuid3 != uuid1);
}

TEST_CASE("Random UUID generation") {
	const auto MAX_ITERS = 10'000;

	std::unordered_set<std::string> uuids;

	for (unsigned i = 0; i < MAX_ITERS; i++) {
		auto uuid = UUID();

		if (uuids.count((std::string)uuid) > 0) {
			REQUIRE(false);
		}

		uuids.emplace(uuid);
	}
}
