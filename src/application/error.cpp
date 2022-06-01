#include "error.hpp"

HttpException::HttpException(const std::string& msg, int status) :
	msg(msg.c_str()),
	status(status)
	{}

BadRequestException::BadRequestException(const std::string& msg) :
	HttpException(msg, 400)
	{}

UnauthorizedException::UnauthorizedException(const std::string& msg) :
	HttpException(msg, 401)
	{}

NotFoundException::NotFoundException(const std::string& msg) :
	HttpException(msg, 404)
	{}

ServerErrorException::ServerErrorException(const std::string& msg) :
	HttpException(msg, 500)
	{}
