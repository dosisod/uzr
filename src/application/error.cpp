#include "error.hpp"

HttpException::HttpException(const char* msg, int status) :
	msg(msg),
	status(status)
	{}

BadRequestException::BadRequestException(const char *msg) :
	HttpException(msg, 400)
	{}

UnauthorizedException::UnauthorizedException(const char *msg) :
	HttpException(msg, 401)
	{}

NotFoundException::NotFoundException(const char *msg) :
	HttpException(msg, 404)
	{}

ServerErrorException::ServerErrorException(const char *msg) :
	HttpException(msg, 500)
	{}
