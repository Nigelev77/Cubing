cmake_minimum_required(VERSION 3.0)
find_package(OpenGL REQUIRED)
file(GLOB render_src "*.h" "*.cpp")

add_library(render ${render_src} ${FREETYPE_H})
target_include_directories(render PUBLIC ${PROJECT_SOURCE_DIR}/libs)
target_include_directories(render PUBLIC ${PROJECT_SOURCE_DIR}/src/IO)
target_link_libraries(render PUBLIC glad ${PROJECT_SOURCE_DIR}/libs/GLFW/lib/libglfw3.a)
target_link_libraries(render PUBLIC ${PROJECT_SOURCE_DIR}/libs/freetype_libs/freetype.a)