#include "application/dto/jsonBody.hpp"
#include "domain/repo/groupRepo.hpp"

struct NewGroupDto : NewGroup {
	static NewGroupDto fromJson(const JsonBody&);

	NewGroupDto(const NewGroup& group);
};
