cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This AppDataBaseTest)

add_executable(${This} appdbtest.cpp)

target_link_libraries(${This} gtest_main appdb)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running app database test" POST_BUILD COMMAND ${This})

