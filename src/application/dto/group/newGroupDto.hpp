#include "domain/repo/groupRepo.hpp"

struct NewGroupDto : NewGroup {
	static NewGroupDto fromJson(const std::string& jsonBody);

	NewGroupDto(const NewGroup& group);
};
