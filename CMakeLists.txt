cmake_minimum_required(VERSION 3.11)
project(loggy C)

add_library(loggy SHARED src/loggy.c)
target_include_directories(loggy PUBLIC src)

add_executable(loggy_test test/loggy_test.c)
target_link_libraries(loggy_test PUBLIC loggy)

# Enable CTest
enable_testing()
add_test(NAME loggy_test COMMAND loggy_test)

