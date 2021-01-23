add_executable(test_example   test_example.c)
target_include_directories(test_example PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(example_tests test_example)