cmake_minimum_required(VERSION 3.27)
project(all-stuff)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

set(WORK_PATH "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)
