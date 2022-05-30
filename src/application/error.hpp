#pragma once

#include <exception>
#include <string>

class HttpException : public std::exception {
public:
	HttpException(std::string msg, int status);

	virtual const char* what() const noexcept { return msg; }

	const char* msg;
	const int status;
};

class BadRequestException : public HttpException {
public:
	BadRequestException(std::string msg = "Bad request");
};

class UnauthorizedException : public HttpException {
public:
	UnauthorizedException(std::string msg = "Unauthorized");
};

class NotFoundException : public HttpException {
public:
	NotFoundException(std::string msg = "Not Found");
};

class ServerErrorException : public HttpException {
public:
	ServerErrorException(std::string msg = "Server Error");
};
