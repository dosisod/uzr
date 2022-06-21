#pragma once

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <json.hpp>
using json = nlohmann::json;

#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"
#include "infrastructure/config.hpp"

class GroupRepo : public IGroupRepo {
public:
	GroupRepo(const InfrastructureConfig& config) :
		db(config.dbFilename, SQLite::OPEN_READWRITE) {}

	std::optional<Group> getGroupById(const UUID& uuid) override {
		SQLite::Statement query(db, "SELECT uuid, name, metadata FROM groups WHERE uuid = lower(?)");
		query.bind(1, (std::string)uuid);

		if (!query.executeStep()) return {};

		return Group {
			.id = UUID(query.getColumn(0)),
			.name = query.getColumn(1),
			.metadata = json::parse((std::string)query.getColumn(2)).get<Metadata>()
		};
	}

private:
	SQLite::Database db;
};
