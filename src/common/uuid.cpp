#include <utility>

#include <uuid/uuid.h>

#include "uuid.hpp"

UUID::UUID(const std::string& s) { // NOLINT
	auto error = uuid_parse(s.c_str(), uuid);

	if (error) uuid_clear(uuid);
}

bool UUID::operator ==(const UUID& o) const {
	return uuid_compare(o.uuid, uuid) == 0;
}

bool UUID::operator !=(const UUID& o) const {
	return !(&o == this);
}

UUID::UUID() { // NOLINT
	uuid_generate(uuid);
}

UUID::operator bool() const {
	return !uuid_is_null(uuid);
}

UUID::operator std::string() const {
	char out[37] = {0}; // NOLINT
	uuid_unparse_upper(uuid, out);
	return {out};
}
