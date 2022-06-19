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
}
