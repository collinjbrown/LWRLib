# CMakeList.txt : CMake project for LWRLib.

cmake_minimum_required (VERSION 3.22)
project (LWRLib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set (DEBUG True)

add_library(LWRLib
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
    "src/spriterenderer.cpp"
    "src/spriterenderer.h"
    "src/textrenderer.cpp"
    "src/textrenderer.h"
    "src/texture.cpp"
    "src/texture.h"
    "src/util.cpp"
    "src/util.h")

if(DEBUG)
    add_subdirectory(libs/freetype-2.12.1)
    add_subdirectory(libs/glad)
    add_subdirectory(libs/glfw-3.3.8)
    add_subdirectory(libs/glm-0.9.9.8)
endif()

target_link_libraries(LWRLib glfw glad glm freetype)
target_include_directories (LWRLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
