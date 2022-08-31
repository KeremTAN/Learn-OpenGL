cmake_minimum_required(VERSION 2.8)

project(OpenGL)

set (PROJECT_DIR ${CMAKE_SOURCE_DIR})

set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/lib.cpp)

set(PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/lib.hpp
    ${PROJECT_INCLUDE_DIR}/GLFW/glfw3.h
    ${PROJECT_INCLUDE_DIR}/GLFW/glfw3.h
    )

include_directories(${PROJECT_INCLUDE_DIR})

link_libraries(${PROJECT_DIR}/lib/libglfw.3.3.dylib)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})