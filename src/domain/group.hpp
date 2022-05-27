#pragma once

#include <string>
#include <vector>

struct Group {
	unsigned long id;
	std::string name;
	std::vector<std::string> users; // TODO: dont include user list in group
};
