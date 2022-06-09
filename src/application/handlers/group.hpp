#pragma once

#include "domain/repo/groupRepo.hpp"

#include "../dto/group/groupDto.hpp"

GroupDto getGroupByIdQuery(IGroupRepo&, unsigned);
