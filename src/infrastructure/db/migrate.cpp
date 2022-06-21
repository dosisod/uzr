#include <iostream>
#include <string>

#include <SQLiteCpp/Database.h>

#include "../config.hpp"

unsigned getMigrationVersion(const SQLite::Database& db);
void run(SQLite::Database& db);

#include "./migrations.hpp"

int main() {
	InfrastructureConfig config;

	try {
		SQLite::Database db(
			config.dbFilename,
			SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE
		);

		run(db);
	}
	catch (std::exception& e) {
		std::cerr << "uzr_migrate: " << e.what() << "\n";
		return 1;
	}

	std::cout << "uzr_migrate: Migration successful\n";

	return 0;
}

void run(SQLite::Database& db) {
	switch (getMigrationVersion(db)) {
		case 0: db.exec(MIGRATION_0); [[fallthrough]];
		case 1: db.exec(MIGRATION_1);
	}
}

unsigned getMigrationVersion(const SQLite::Database& db) {
	try {
		SQLite::Statement query(db, "SELECT version FROM migration_version");

		query.executeStep();

		return query.getColumn(0);
	}
	catch (std::exception&) {
		return 0;
	}
}
