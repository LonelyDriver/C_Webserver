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
set(VERSION_PATCH "0")
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(TESTS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tests)

configure_file("config_version.h.in"
    ${CMAKE_SOURCE_DIR}/include/config_version.h)

find_package(Threads)

option(testing "Execute tests" OFF)

add_executable(socket_example src/examples/socket_example.c)
target_include_directories(socket_example PRIVATE include)

add_executable(thread_example src/examples/thread_example.c)
target_include_directories(thread_example PRIVATE include/threads)
target_link_libraries(thread_example Threads::Threads)

add_executable(web_serv_example src/examples/web_serv_example.c)
target_include_directories(
    web_serv_example 
    PRIVATE include
    include 
    include/threads)
target_link_libraries(web_serv_example Threads::Threads)

add_subdirectory(src)
add_subdirectory(Unity)

if(testing)
add_subdirectory(tests)
endif()