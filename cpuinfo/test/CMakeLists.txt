cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This CPUInfoTest)

add_executable(${This} cpuinfotest.cpp)

target_link_libraries(${This} gtest_main cpuinfo)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running cpu information test" POST_BUILD COMMAND ${This})

