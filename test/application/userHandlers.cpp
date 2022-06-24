#include "catch.hpp"
#include "fakeit.hpp"
using namespace fakeit;

#include "application/error.hpp"
#include "application/handlers/user/loginCommandHandler.hpp"
#include "domain/repo/userRepo.hpp"

TEST_CASE("Login handler fails when login fails") {
	Mock<IUserRepo> mock;
	When(Method(mock, isValidLogin)).Return(false);

	auto loginDto = LoginDto({
		.username = "any username",
		.password = "any password"
	});

	auto cmd = LoginCommandHandler(mock.get());
	REQUIRE_THROWS_AS(cmd.handle(loginDto), UnauthorizedException);

	Verify(Method(mock, isValidLogin)).Once();
}

TEST_CASE("Login handler returns user upon successful login") {
	auto userDto = UserDto({
		.id = UUID(),
		.username = "bob"
	});

	auto loginDto = LoginDto({
		.username = "bob",
		.password = "some password"
	});

	Mock<IUserRepo> mock;
	When(Method(mock, isValidLogin)).Return(true);
	When(Method(mock, getByUsername)).Return(userDto);

	auto cmd = LoginCommandHandler(mock.get());
	auto resp = cmd.handle(loginDto);

	CHECK(resp.username == "bob");

	Verify(Method(mock, isValidLogin)).Once();
	Verify(Method(mock, getByUsername)).Once();
}
