#pragma once

#include <json.hpp>
using json = nlohmann::json;

class JsonBody : public json {
public:
	JsonBody(const std::string& j) : json(json::parse(j)) {}
};
