# CMakeList.txt : CMake project for LWRLib.

cmake_minimum_required (VERSION 3.22)
project (LWRLib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_ROOT ~/LWRLib/)
add_library(LWRLib SHARED
    "src/external/stb_image.cpp"
    "src/external/stb_image.h"
    "src/archtexture.h"
    "src/hub.cpp"
    "src/hub.h"
    "src/inputhandler.cpp"
    "src/inputhandler.h"
    "src/polygons.h"
    "src/renderer.cpp"
    "src/renderer.h"
    "src/shader.cpp"
    "src/shader.h"
    "src/texture.cpp"
    "src/texture.h"
    "src/util.cpp"
    "src/util.h")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw-3.3.8")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/glad")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/glm-0.9.9.8")

target_include_directories(LWRLib PRIVATE .)
set_target_properties(LWRLib PROPERTIES VERSION 0.1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(LWRLib PUBLIC glfw glad glm)

install(TARGETS LWRLib DESTINATION ${CMAKE_INSTALL_LIBDIR})
