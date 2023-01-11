cmake_minimum_required(VERSION 3.0.0)
project(Cubing VERSION 0.1.0)

include_directories(libs/GLAD/include)
include_directories(libs/GLFW/include)

find_package(OpenGL REQUIRED)

add_executable(Cubing main.cpp)
target_link_libraries(Cubing ${CMAKE_SOURCE_DIR}/libs/GLFW/lib/libglfw3.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)