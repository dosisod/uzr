#pragma once

#include <exception>

class ValidationError : public std::exception {
public:
	ValidationError(const char* msg) : msg(msg) {}

	virtual const char* what() noexcept { return msg; }

	const char* msg;
};
