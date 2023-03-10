cmake_minimum_required(VERSION 3.13)
project(Cubing VERSION 0.1.0)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs/GLAD/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/GLFW/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)

find_package(OpenGL REQUIRED)
add_subdirectory(libs/GLAD)
add_subdirectory(src/Render)
add_subdirectory(src/Toolbox)
add_subdirectory(src/IO)

add_executable(Cubing main.cpp)
target_link_libraries(Cubing PUBLIC render)
target_link_libraries(Cubing PUBLIC toolbox)
target_link_libraries(Cubing PUBLIC io)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)