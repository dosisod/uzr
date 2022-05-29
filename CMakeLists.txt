cmake_minimum_required(VERSION 3.21.3)

project(uzr VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(httplib OBJECT src/vendor/httplib.cc)

add_library(json OBJECT src/vendor/json.hpp)
target_precompile_headers(json PUBLIC src/vendor/json.hpp)

include_directories(src)
include_directories(src/vendor)

add_executable(
	uzr
	src/main.cpp
	src/application/handlers/group.cpp
	src/application/handlers/user.cpp
	src/application/app.cpp
	src/application/error.cpp
	src/application/config.cpp
	src/application/routes/health.cpp
	src/application/routes/auth.cpp
	src/application/routes/group.cpp
)
set_target_properties(uzr PROPERTIES COMPILE_FLAGS "-g -O0 -Wall -Wextra -pedantic -Werror")
target_link_libraries(uzr PRIVATE httplib crypt json pthread)

add_executable(
	test_uzr
	test/test.cpp
)
set_target_properties(test_uzr PROPERTIES COMPILE_FLAGS "-g -O0 -Wall -Wextra -pedantic -Werror")
