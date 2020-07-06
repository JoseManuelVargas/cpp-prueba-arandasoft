cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(fileinfo)

enable_testing()

add_subdirectory(test)

if (WIN32)
        add_library(${PROJECT_NAME} src/fileinfo_win.cpp)
	# elseif(APPLE)
	# add_library(${PROJECT_NAME} src/fileinfo_macos.cpp)
else()
        add_library(${PROJECT_NAME} src/fileinfo_unix.cpp)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)

