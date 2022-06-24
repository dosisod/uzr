#pragma once

#include <string>

#include <SQLiteCpp/Database.h>

int migrate(const std::string& dbFilename, bool quiet=false);
unsigned getMigrationVersion(const SQLite::Database& db);
