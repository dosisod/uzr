#include "application/handlers/group/getGroupByIdQueryHandler.hpp"
#include "domain/repo/groupRepo.hpp"
#include "presentation/di.hpp"

#include "group.hpp"

namespace route::group {
	void getById(const Request& req, Response& res) {
		const unsigned gid = std::stoi(req.matches[1]);

		auto cmd = DiCreate<GetGroupByIdQueryHandler>();
		auto resp = cmd.handle(gid);

		res.set_content(resp, "text/json");
	}
}
