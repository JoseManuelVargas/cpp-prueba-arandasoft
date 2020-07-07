cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(prueba-arandasoft)

enable_testing()


add_subdirectory(googletest)
add_subdirectory(soci)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/soci/include)

add_subdirectory(cpuinfo)
add_subdirectory(fileinfo)
add_subdirectory(appdb)


add_executable(${PROJECT_NAME} main.cpp)


