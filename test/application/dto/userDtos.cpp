#include "catch.hpp"

#include "application/dto/user/loginDto.hpp"
#include "application/dto/user/newUserInfoDto.hpp"
#include "application/dto/user/userDto.hpp"
#include "common/uuid.hpp"

TEST_CASE("Create and stringify user") {
	UUID id("454b3b96-9dc6-4d4c-a085-9aa8c7470524");

	auto dto = UserDto(User {
		.id = id,
		.username = "bob",
		.metadata = {{"key", "value"}}
	});

	const auto* expected = R"({"id":"454b3b96-9dc6-4d4c-a085-9aa8c7470524","metadata":{"key":"value"},"username":"bob"})";

	CHECK((std::string)dto == expected);
}

TEST_CASE("Create LoginDto from JSON") {
	std::string jsonBody = R"({"username":"admin","password":"123"})";

	auto dto = LoginDto::fromJson(jsonBody);

	CHECK(dto.username == "admin");
	CHECK(dto.password == "123");
}

TEST_CASE("Create NewUserInfo from JSON") {
	std::string jsonBody = R"({"username":"admin","password":"123","metadata":{"key":"value"}})";

	auto dto = NewUserInfoDto::fromJson(jsonBody);

	CHECK(dto.username == "admin");
	CHECK(dto.password == "123");
	REQUIRE(dto.metadata.has_value());
	CHECK((*dto.metadata)["key"] == "value");
}
