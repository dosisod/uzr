#include "application/handlers/group/addGroupCommandHandler.hpp"
#include "application/handlers/group/getGroupByIdQueryHandler.hpp"
#include "domain/repo/groupRepo.hpp"
#include "presentation/di.hpp"

#include "group.hpp"

namespace route::group {
	void getById(const Request& req, Response& res) {
		auto cmd = DiCreate<GetGroupByIdQueryHandler>();
		auto resp = cmd.handle(UUID(req.matches[1]));

		res.set_content(resp, "text/json");
	}

	void addGroup(const Request& req, Response& res) {
		auto cmd = DiCreate<AddGroupCommandHandler>();
		auto resp = cmd.handle(NewGroupDto::fromJson(req.body));

		res.set_content(resp, "text/json");
	}
}
