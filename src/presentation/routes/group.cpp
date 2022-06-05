#include "application/handlers/group.hpp"

#include "group.hpp"

namespace route::group {
	void getById(const Request& req, Response& res) {
		const unsigned gid = std::stoi(req.matches[1]);

		auto groupRepo = GroupRepo();

		res.set_content(getGroupByIdQuery(groupRepo, gid), "text/json");
	}
}
