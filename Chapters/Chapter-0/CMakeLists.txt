cmake_minimum_required(VERSION 2.8)

project(Udemy-OpenGL)

set (PROJECT_DIR ${CMAKE_SOURCE_DIR})

set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp)

set(PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/GLFW/
    ${PROJECT_INCLUDE_DIR}/GLEW/
    )

file(GLOB PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIRS}/*.h
)
include_directories(${PROJECT_INCLUDE_DIR})

link_libraries(
    ${PROJECT_DIR}/lib/libglfw.3.3.dylib
    ${PROJECT_DIR}/lib/libGLEW.dylib
    "-framework OpenGL" # OpenGL lib for mac
    # -lGL              # OpenGL lib for linux
    # -lopengl32        # OpenGL lib for windows
) 

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})