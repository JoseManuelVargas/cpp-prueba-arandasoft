cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(socket)

enable_testing()

add_subdirectory(test)

if (WIN32)
	add_library(${PROJECT_NAME} src/socket_win32.cpp)
	target_link_libraries(${PROJECT_NAME} wsock32 ws2_32 advapi32)
else()
	add_library(${PROJECT_NAME} src/socket_unix.cpp)
endif()


target_include_directories(${PROJECT_NAME} PUBLIC include)

