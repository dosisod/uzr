#pragma once

#include <exception>
#include <string>

class ValidationError : public std::exception {
public:
	ValidationError(const std::string& msg) : msg(msg.c_str()) {}

	[[nodiscard]] const char* what() const noexcept override { return msg; }

	const char* msg;
};
