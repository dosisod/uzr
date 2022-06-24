#include "migrate.hpp"
#include "../config.hpp"

int main() {
	InfrastructureConfig config;

	migrate(config.dbFilename);
}
