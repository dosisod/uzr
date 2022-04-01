cmake_minimum_required(VERSION 3.21.3)

project(uzr VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(httplib OBJECT src/vendor/httplib.cc)

add_library(json OBJECT src/vendor/json.hpp)
target_precompile_headers(json PUBLIC src/vendor/json.hpp)

include_directories(src/vendor)
add_executable(uzr src/main.cpp src/api.cpp src/group.cpp src/user.cpp)
set_target_properties(uzr PROPERTIES COMPILE_FLAGS "-g -O0 -Wall -Wextra -pedantic -Werror")
target_link_libraries(uzr PRIVATE httplib crypt json pthread)
