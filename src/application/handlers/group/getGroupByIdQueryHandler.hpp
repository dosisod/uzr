#pragma once

#include "domain/repo/groupRepo.hpp"

#include "application/dto/group/groupDto.hpp"

class GetGroupByIdQueryHandler {
public:
	GetGroupByIdQueryHandler(IGroupRepo& repo);

	GroupDto handle(unsigned gid);

private:
	IGroupRepo& repo;
};
