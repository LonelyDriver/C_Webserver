cmake_minimum_required(VERSION 3.15)
project(Webservero C)

set(CMAKE_C_STANDARD 11)

if(WIN32)
set(COMPILE_OPTIONS)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS)
elseif(UNIX)
set(COMPILE_OPTIONS -Wall -Wextra -pendatic -Werror -fstack-protector)
set(CMAKE_BUILD_TYPE "Release")
endif()

set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "1")
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(TESTS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tests)

configure_file("config_version.h.in"
    ${CMAKE_SOURCE_DIR}/include/config_version.h)

find_package(Threads)

option(testing "Execute tests" OFF)

add_executable(testo src/examples/example1.c
    src/error_handling.c)
target_include_directories(testo PRIVATE include)
if(UNIX)
target_sources(testo PRIVATE src/socketo_linux.c)
elseif(WIN32)
message("Socket abstraction layer for windows not implemented")
endif()

#add_subdirectory(include)