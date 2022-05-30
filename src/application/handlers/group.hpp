#include <string>

#include "infrastructure/repo/groupRepo.hpp"

struct GroupDto : Group {
	operator std::string() const;

	GroupDto(const Group& g);
};

GroupDto getGroupByIdQuery(IGroupRepo&, unsigned);
