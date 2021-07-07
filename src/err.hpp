#include <exception>

class HttpException : public std::exception {
public:
	HttpException(const char* msg, int status) :
		msg(msg),
		status(status)
		{ }

	virtual const char* what() noexcept { return msg; }

	const char* msg;
	const int status;
};

class BadRequestException : public HttpException {
public:
	BadRequestException(const char *msg = "Bad request") :
		HttpException(msg, 400) { }
};

class UnauthorizedException : public HttpException {
public:
	UnauthorizedException(const char *msg = "Unauthorized") :
		HttpException(msg, 401) { }
};

class NotFoundException : public HttpException {
public:
	NotFoundException(const char *msg = "Not Found") :
		HttpException(msg, 404) { }
};

class ServerErrorException : public HttpException {
public:
	ServerErrorException(const char *msg = "Server Error") :
		HttpException(msg, 500) { }
};
