cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This FileInfoTest)

add_executable(${This} fileinfotest.cpp)

target_link_libraries(${This} gtest_main fileinfo)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running files information test" POST_BUILD COMMAND ${This})
