#pragma once

#include <string>

#include <uuid/uuid.h>

class UUID {
public:
	UUID();
	UUID(const std::string& s);

	explicit operator bool() const;
	explicit operator std::string() const;
	bool operator ==(const UUID& o) const;

private:
	uuid_t uuid;
};
