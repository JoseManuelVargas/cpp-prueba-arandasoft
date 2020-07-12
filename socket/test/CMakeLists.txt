cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(This SocketTest)

add_executable(${This} sockettest.cpp)

target_link_libraries(${This} gtest_main BosmaScheduler socket)

add_test(NAME ${This} COMMAND ${This})

add_custom_command(TARGET ${This} COMMENT "Running sockets test" POST_BUILD COMMAND ${This})

