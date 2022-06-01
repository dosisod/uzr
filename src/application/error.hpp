#pragma once

#include <exception>
#include <string>

class HttpException : public std::exception {
public:
	HttpException(const std::string& msg, int status);

	[[nodiscard]] const char* what() const noexcept override { return msg; }

	const char* msg;
	const int status;
};

class BadRequestException : public HttpException {
public:
	BadRequestException(const std::string& msg = "Bad request");
};

class UnauthorizedException : public HttpException {
public:
	UnauthorizedException(const std::string& msg = "Unauthorized");
};

class NotFoundException : public HttpException {
public:
	NotFoundException(const std::string& msg = "Not Found");
};

class ServerErrorException : public HttpException {
public:
	ServerErrorException(const std::string& msg = "Server Error");
};
