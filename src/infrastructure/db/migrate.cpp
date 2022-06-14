#include <iostream>
#include <string>

#include <SQLiteCpp/Database.h>

constexpr auto DEFAULT_DB_FILENAME = "/etc/uzr_db.db3";

void run(const std::string& dbFilename) {
	SQLite::Database db(dbFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

	db.exec(R"(
		CREATE TABLE IF NOT EXISTS users (
			uuid TEXT NOT NULL UNIQUE,
			username TEXT NOT NULL UNIQUE,
			password_hash TEXT NOT NULL
		);

		CREATE TABLE IF NOT EXISTS groups (
			uuid TEXT NOT NULL UNIQUE,
			name TEXT NOT NULL UNIQUE
		);

		CREATE TABLE IF NOT EXISTS _groups_users (
			group_uuid TEXT NOT NULL,
			user_uuid TEXT NOT NULL
		);
	)");
}

int main() {
	const char* env = std::getenv("DB_FILENAME");

	std::string dbFilename = env == nullptr ? DEFAULT_DB_FILENAME : env;

	try {
		run(dbFilename);
	}
	catch (std::exception& e) {
		std::cerr << "uzr_migrate: " << e.what() << "\n";
		return 1;
	}

	std::cout << "uzr_migrate: Migration successful\n";

	return 0;
}
