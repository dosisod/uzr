#pragma once

#include <string_view>

#include <SQLiteCpp/Database.h>

int migrate(std::string_view dbFilename, bool quiet=false);
unsigned getMigrationVersion(const SQLite::Database& db);
