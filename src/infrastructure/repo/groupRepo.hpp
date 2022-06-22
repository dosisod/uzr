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

	std::optional<Group> addGroup(const NewGroup& group) override {
		SQLite::Statement query(db, "SELECT name FROM groups WHERE name = ?");
		query.bind(1, group.name);

		if (query.executeStep()) return {};

		UUID id;
		auto metadata = group.metadata.value_or(Metadata{});

		query = SQLite::Statement(db, "INSERT INTO groups VALUES (?, ?, ?)");
		query.bind(1, (std::string)id);
		query.bind(2, group.name);
		query.bind(3, json(metadata).dump());

		query.exec();

		return Group {
			.id = id,
			.name = group.name,
			.metadata = metadata
		};
	}

private:
	SQLite::Database db;
};
