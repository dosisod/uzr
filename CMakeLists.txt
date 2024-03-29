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

add_subdirectory(src/vendor/SQLiteCpp)
include_directories(src/vendor/SQLiteCpp/include)

file(GLOB_RECURSE libuzr_SRC CONFIGURE_DEPENDS "src/application/**.cpp" "src/common/**.cpp")
add_library(libuzr OBJECT ${libuzr_SRC})

# TODO(dosisod): convert repos to use .cpp files, exlude main() from db migration folder
file(GLOB_RECURSE uzr_api_SRC CONFIGURE_DEPENDS "src/presentation/**.cpp" "src/infrastructure/config.cpp" "src/infrastructure/repo/*.cpp")
add_executable(uzr src/main.cpp ${uzr_api_SRC})
target_link_libraries(uzr PRIVATE httplib crypt SQLiteCpp sqlite3 dl json pthread uuid libuzr)

file(GLOB_RECURSE uzr_migrate_SRC CONFIGURE_DEPENDS src/infrastructure/db/migrate.cpp)
add_library(libuzr_migrate OBJECT ${uzr_migrate_SRC} src/infrastructure/config.cpp)
add_executable(uzr_migrate src/infrastructure/db/main.cpp)
target_link_libraries(uzr_migrate PRIVATE libuzr_migrate SQLiteCpp sqlite3)

# TODO(dosisod): make seperate library/source list for infra code
file(GLOB_RECURSE test_SRC CONFIGURE_DEPENDS "test/**.cpp" "src/infrastructure/repo/*.cpp")
add_executable(test_uzr ${test_SRC})
target_link_libraries(test_uzr PRIVATE SQLiteCpp sqlite3 crypt uuid libuzr libuzr_migrate)

set_target_properties(libuzr uzr uzr_migrate test_uzr PROPERTIES COMPILE_FLAGS "${COMMON_FLAGS}")
