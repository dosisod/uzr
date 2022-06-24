#include "./loginDto.hpp"

LoginDto LoginDto::fromJson(const JsonBody& parsed) {
	LoginDto login = {{
		.username = parsed.value("username", ""),
		.password = parsed.value("password", "")
	}};

	login.validate();

	return login;
}

LoginDto::LoginDto(const Login& l) : Login(l) {}
