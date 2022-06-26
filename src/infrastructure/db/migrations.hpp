constexpr auto MIGRATION_0 = R"(
	CREATE TABLE users (
		uuid TEXT NOT NULL UNIQUE,
		username TEXT NOT NULL UNIQUE,
		password_hash TEXT NOT NULL
	);

	CREATE TABLE groups (
		uuid TEXT NOT NULL UNIQUE,
		name TEXT NOT NULL UNIQUE
	);

	CREATE TABLE _groups_users (
		group_uuid TEXT NOT NULL,
		user_uuid TEXT NOT NULL
	);

	CREATE TABLE migration_version (
		version INT NOT NULL
	);

	INSERT INTO migration_version VALUES (1);
)";

constexpr auto MIGRATION_1 = R"(
	ALTER TABLE users ADD COLUMN metadata TEXT;

	ALTER TABLE groups ADD COLUMN metadata TEXT;

	UPDATE migration_version SET version = 2;
)";

constexpr auto MIGRATION_2 = R"(
	CREATE TABLE roles (
		id INT NOT NULL PRIMARY KEY,
		name TEXT NOT NULL UNIQUE
	);

	UPDATE migration_version SET version = 3;
)";
