#include "application/error.hpp"

#include "./addGroupCommandHandler.hpp"

AddGroupCommandHandler::AddGroupCommandHandler(IGroupRepo& repo) :
	repo(repo) {}

GroupDto AddGroupCommandHandler::handle(const NewGroupDto& newGroup) {
	auto group = repo.addGroup(newGroup);

	if (!group.has_value()) {
		throw BadRequestException("Group already exists");
	}

	return {*group};
}
