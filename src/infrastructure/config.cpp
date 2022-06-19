#include "./config.hpp"

// TODO(dosisod): set this default via CMake (so it can be used in docker)
constexpr auto DEFAULT_DB_FILENAME = "/etc/uzr_db.db3";

static std::string dbFilenameOrDefault() {
	const char* env = std::getenv("DB_FILENAME");

	return env == nullptr ? DEFAULT_DB_FILENAME : env;
}

InfrastructureConfig::InfrastructureConfig() :
	dbFilename(dbFilenameOrDefault()) {}
