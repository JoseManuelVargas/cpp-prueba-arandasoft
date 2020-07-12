cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(taskmanager)

enable_testing()

add_subdirectory(test)

add_library(${PROJECT_NAME} src/taskmanager.cpp)

target_link_libraries(${PROJECT_NAME} appdb cpuinfo fileinfo nlohmann_json BosmaScheduler socket)

target_include_directories(${PROJECT_NAME} PUBLIC include)

