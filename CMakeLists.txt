cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(prueba-arandasoft)

enable_testing()


add_subdirectory(googletest)
add_subdirectory(soci)

if(WIN32)
	include_directories(${SQLITE3_INCLUDE_DIR})
elseif(APPLE)
	set(CMAKE_MACOSX_RPATH 1)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/soci/include)

add_subdirectory(json)
add_subdirectory(scheduler)

add_subdirectory(cpuinfo)
add_subdirectory(fileinfo)
add_subdirectory(appdb)
add_subdirectory(socket)
add_subdirectory(taskmanager)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} taskmanager)

