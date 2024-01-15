
cmake_minimum_required(VERSION 3.27.7)

project(
  Convict
  VERSION 7.0.0
)
include(FetchContent)

# Formatting library
FetchContent_Declare(
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 5.3.0)

FetchContent_MakeAvailable(fmtlib)

set( CMAKE_VERBOSE_MAKEFILE on )

set(
  SRC
  main.cpp
  database.cpp
  database.hpp
)
add_executable(
  ${PROJECT_NAME}
	${SRC}
  ${CMAKE_SOURCE_DIR}/rlImGui/rlImGui.cpp
  ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
  ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
  ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
  ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
  ${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
  sqlite3.c
  ${RESOURCE_FILES}
)
include_directories(
  ${CMAKE_SOURCE_DIR}/raylib/src
  ${CMAKE_SOURCE_DIR}/imgui
  ${CMAKE_SOURCE_DIR}/rlImGui
)
target_link_libraries(
  ${PROJECT_NAME}
  fmt::fmt
  ${CMAKE_SOURCE_DIR}/raylib/build/raylib/libraylib.a
  -pthread
  GL
  m
  dl
)

#module with helper functions
include(gwf_module)

fix_format(${CMAKE_SOURCE_DIR}/src ${SRC} )

