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

add_executable(testo src/examples/example1.c)
target_include_directories(testo PRIVATE include)

add_executable(thread_test src/examples/thread_example.c)
target_include_directories(thread_test PRIVATE include/threads)
target_link_libraries(thread_test Threads::Threads)

add_subdirectory(src)

if(testing)
add_subdirectory(tests)
endif()