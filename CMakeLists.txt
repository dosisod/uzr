cmake_minimum_required(VERSION 3.21.3)

project(uzr VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMMON_FLAGS "-g -O0 -Wall -Wextra -pedantic -Werror")

add_library(httplib OBJECT src/vendor/httplib.cc)

add_library(json OBJECT src/vendor/json.hpp)
target_precompile_headers(json PUBLIC src/vendor/json.hpp)

include_directories(src)
include_directories(src/vendor)

file(GLOB_RECURSE libuzr_SRC CONFIGURE_DEPENDS "src/application/**.cpp")
add_library(libuzr OBJECT ${libuzr_SRC})

add_executable(uzr src/main.cpp)
target_link_libraries(uzr PRIVATE httplib crypt json pthread libuzr)

file(GLOB_RECURSE test_SRC CONFIGURE_DEPENDS "test/**.cpp")
add_executable(test_uzr ${test_SRC})
target_link_libraries(test_uzr PRIVATE httplib crypt pthread libuzr)

set_target_properties(libuzr uzr test_uzr PROPERTIES COMPILE_FLAGS "${COMMON_FLAGS}")
