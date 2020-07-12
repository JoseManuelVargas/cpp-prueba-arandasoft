cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This ScheduleTest)

add_executable(${This} scheduletest.cpp)

target_link_libraries(${This} gtest_main BosmaScheduler)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running schedule test" POST_BUILD COMMAND ${This})

