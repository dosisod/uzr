#include "catch.hpp"

#include "common/uuid.hpp"
#include "infrastructure/config.hpp"
#include "infrastructure/repo/userRepo.hpp"
#include "temporaryDb.hpp"

TEST_CASE("conversion of UUID to crypt salt") {
	// just some random UUID, could be anything
	UUID uuid("47419cde-063d-4907-a346-6100e09a8a24");

	std::string salt = uuidToCryptSalt(uuid);
	std::string expected = "R0Gc3gY9SQejRmEA4JqKJA";

	CHECK(salt == expected);
}

TEST_CASE("users can be added and retrieved") {
	TemporaryDb db;
	InfrastructureConfig config;
	config.dbFilename = db.filename;

	UserRepo repo(config);

	NewUserInfo newUser {
		.username = "username",
		.password = "password",
		.metadata = Metadata{{ "key", "value" }}
	};

	repo.addUser(newUser);

	auto user = repo.getByUsername("username");

	REQUIRE(user.has_value());
	CHECK(user->id);
	CHECK(user->username == "username");
	CHECK(user->metadata["key"] == "value");
}

TEST_CASE("user login validation") {
	TemporaryDb db;
	InfrastructureConfig config;
	config.dbFilename = db.filename;

	UserRepo repo(config);

	SECTION("unknown username will fail") {
		REQUIRE_FALSE(repo.isValidLogin(Login {
			.username = "unknown username",
			.password = "any password"
		}));
	}

	NewUserInfo newUser {
		.username = "username",
		.password = "password",
	};

	repo.addUser(newUser);

	SECTION("correct username and password will succeed") {
		REQUIRE(repo.isValidLogin(Login {
			.username = "username",
			.password = "password"
		}));
	}

	SECTION("correct username but incorrect password will fail") {
		REQUIRE_FALSE(repo.isValidLogin(Login {
			.username = "username",
			.password = "invalid password"
		}));
	}
}
