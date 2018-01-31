
cmake_minimum_required(VERSION 3.5)

project(Convict)
set(GLFW_VERSION 1)
set(GLFW_VERSION_FULL 5)
set(ICON glfw.icns)

set(RESOURCE_FILES
  glfw.icns
  convict.db
)

include_directories("${CMAKE_SOURCE_DIR}/deps")
include_directories("${CMAKE_SOURCE_DIR}/GL")
include_directories("${CMAKE_SOURCE_DIR}/GLFW")

set(GLAD "${CMAKE_SOURCE_DIR}/deps/glad/glad.h"
         "${CMAKE_SOURCE_DIR}/deps/glad.c")


add_subdirectory(glfw-3.2.1)

if (APPLE)
	add_executable(${PROJECT_NAME}
    main.cpp
    util.mm
    Model.cpp
    sqlite3.c
    imgui_demo.cpp
    gl3w.c
    imgui_impl_glfw_gl3.cpp
    imgui.cpp
    imgui_draw.cpp
    ${RESOURCE_FILES} ${GLAD})

	target_link_libraries(${PROJECT_NAME}
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework Cocoa"
    glfw)

  set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_FRAMEWORK_IDENTIFIER org.gwf.${PROJECT_NAME}
    RESOURCE "${RESOURCE_FILES}")

elseif (UNIX AND NOT APPLE)

  configure_file(${CMAKE_SOURCE_DIR}/convict.db ./convict.db COPYONLY)
  configure_file(${CMAKE_SOURCE_DIR}/alarm.mp3 ./alarm.mp3 COPYONLY)
	add_executable(${PROJECT_NAME}
		main.cpp
    Model.cpp
    sqlite3.c
    imgui_demo.cpp
    gl3w.c
    imgui_impl_glfw_gl3.cpp
    imgui.cpp
    imgui_draw.cpp
    ${RESOURCE_FILES} ${GLAD})

	target_link_libraries(${PROJECT_NAME}
  "-lrt"
  "-lm"
  "-lX11"
  "-lXxf86vm"
  "-lGL"
  "-pthread"
  "-ldl"
  glfw)

endif()
