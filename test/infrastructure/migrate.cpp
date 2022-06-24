#include <filesystem>

#include "catch.hpp"

#include "infrastructure/db/migrate.hpp"
#include "temporaryDb.hpp"

TEST_CASE("Running migration on temp db") {
	std::string dbFilename = "/tmp/temp.db3";

	auto err = migrate(dbFilename, true);
	REQUIRE_FALSE(err);

	SQLite::Database db(dbFilename);
	auto migrationVersion = getMigrationVersion(db);

	CHECK(migrationVersion > 0);

	std::filesystem::remove(dbFilename);
}

TEST_CASE("Test TemporaryDb fixture") {
	std::string filename;

	{
		TemporaryDb db;
		filename = db.filename;

		REQUIRE(std::filesystem::exists(filename));
	}

	REQUIRE_FALSE(std::filesystem::exists(filename));
}
