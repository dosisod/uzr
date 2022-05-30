#include <string>

#include "infrastructure/repo/groupRepo.hpp"

struct GroupDto : Group {
	operator std::string() const;
};

GroupDto getGroupByIdQuery(IGroupRepo&, unsigned);
