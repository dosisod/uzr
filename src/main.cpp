#include "presentation/api.hpp"
#include "presentation/config.hpp"

int main() {
	ApiConfig config;

	Api api(config);

	return api.serve();
}
