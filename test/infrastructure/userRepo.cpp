#include "catch.hpp"

#include "common/uuid.hpp"
#include "infrastructure/repo/userRepo.hpp"

TEST_CASE("conversion of UUID to crypt salt") {
	// just some random UUID, could be anything
	UUID uuid("47419cde-063d-4907-a346-6100e09a8a24");

	std::string salt = uuidToCryptSalt(uuid);
	std::string expected = "R0Gc3gY9SQejRmEA4JqKJA==";

	CHECK(salt == expected);
}
