#pragma once

#include <grp.h>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"
#include "infrastructure/config.hpp"

class GroupRepo : public IGroupRepo {
public:
	GroupRepo(const InfrastructureConfig& config) :
		db(config.dbFilename, SQLite::OPEN_READWRITE) {}

	std::optional<Group> getGroupById(const UUID& uuid) override {
		SQLite::Statement query(db, "SELECT uuid, name FROM groups WHERE uuid = lower(?)");
		query.bind(1, (std::string)uuid);

		if (!query.executeStep()) return {};

		return Group {
			.id = UUID(query.getColumn(0)),
			.name = query.getColumn(1)
		};
	}

private:
	SQLite::Database db;
};
