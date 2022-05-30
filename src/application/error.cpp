#include "error.hpp"

HttpException::HttpException(std::string msg, int status) :
	msg(msg.c_str()),
	status(status)
	{}

BadRequestException::BadRequestException(std::string msg) :
	HttpException(msg, 400)
	{}

UnauthorizedException::UnauthorizedException(std::string msg) :
	HttpException(msg, 401)
	{}

NotFoundException::NotFoundException(std::string msg) :
	HttpException(msg, 404)
	{}

ServerErrorException::ServerErrorException(std::string msg) :
	HttpException(msg, 500)
	{}
