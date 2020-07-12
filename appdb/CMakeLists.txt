cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(appdb)

enable_testing()

add_subdirectory(test)

add_library(${PROJECT_NAME} src/appdb.cpp)


target_link_libraries(${PROJECT_NAME} soci_core soci_sqlite3 cpuinfo fileinfo)

target_include_directories(${PROJECT_NAME} PUBLIC include)

