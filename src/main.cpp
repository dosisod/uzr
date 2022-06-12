#include "presentation/api.hpp"
#include "presentation/config.hpp"
#include "presentation/di.hpp"

int main() {
	const auto injector = MakeDiInjector();
	GlobalInjector = &injector;

	ApiConfig config;

	Api api(config);

	return api.serve();
}
