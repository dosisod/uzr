#pragma once

#include <exception>
#include <string>

class ValidationError : public std::exception {
public:
	ValidationError(std::string msg) : msg(msg.c_str()) {}

	virtual const char* what() const noexcept { return msg; }

	const char* msg;
};
