#pragma once

#include "infrastructure/db/migrate.hpp"

struct TemporaryDb {
	const std::string filename = "/tmp/uzr_testing_db.db3";

	TemporaryDb() {
		auto err = migrate(filename, true);

		if (err) {
			throw std::runtime_error("Migration failed");
		}
	}

	~TemporaryDb() {
		std::filesystem::remove(filename);
	}
};
