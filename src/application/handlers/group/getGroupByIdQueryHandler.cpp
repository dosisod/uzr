#include <json.hpp>
using json = nlohmann::json;

#include "application/error.hpp"
#include "domain/repo/groupRepo.hpp"

#include "./getGroupByIdQueryHandler.hpp"

GetGroupByIdQueryHandler::GetGroupByIdQueryHandler(IGroupRepo& repo) :
	repo(repo)
	{}

GroupDto GetGroupByIdQueryHandler::handle(const UUID& id) {
	auto group = repo.getGroupById(id);
	if (!group) throw NotFoundException();

	return {group.value()};
}
