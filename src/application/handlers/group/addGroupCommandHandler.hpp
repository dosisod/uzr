#pragma once

#include "application/dto/group/newGroupDto.hpp"
#include "application/dto/group/groupDto.hpp"
#include "domain/group.hpp"
#include "domain/repo/groupRepo.hpp"

class AddGroupCommandHandler {
public:
	AddGroupCommandHandler(IGroupRepo&);

	GroupDto handle(const NewGroupDto&);

private:
	IGroupRepo& repo;
};
