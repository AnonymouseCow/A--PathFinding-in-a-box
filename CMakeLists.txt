cmake_minimum_required(VERSION 3.10)

project(pathing LANGUAGES CXX)

file(GLOB SOURCES "src/*")

add_executable(pathing ${SOURCES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_include_directories(pathing PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(pathing PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
