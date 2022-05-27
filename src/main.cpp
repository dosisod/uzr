#include "application/app.hpp"
#include "application/config.hpp"

int main() {
	ApplicationConfig config;

	App app(config);

	return app.serve();
}
