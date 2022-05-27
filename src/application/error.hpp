#pragma once

#include <exception>

class HttpException : public std::exception {
public:
	HttpException(const char* msg, int status);

	virtual const char* what() noexcept { return msg; }

	const char* msg;
	const int status;
};

class BadRequestException : public HttpException {
public:
	BadRequestException(const char *msg = "Bad request");
};

class UnauthorizedException : public HttpException {
public:
	UnauthorizedException(const char *msg = "Unauthorized");
};

class NotFoundException : public HttpException {
public:
	NotFoundException(const char *msg = "Not Found");
};

class ServerErrorException : public HttpException {
public:
	ServerErrorException(const char *msg = "Server Error");
};
