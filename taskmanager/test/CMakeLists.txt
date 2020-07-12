cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This TaskManagerTest)

add_executable(${This} taskmanagertest.cpp)

target_link_libraries(${This} gtest_main taskmanager socket)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running task manager test" POST_BUILD COMMAND ${This})

