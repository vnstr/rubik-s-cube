cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

project(rubik-s-cube)

find_package(glfw3 3.3.8 REQUIRED)
find_package(OpenGL REQUIRED)


add_executable(${PROJECT_NAME}
  SourceFiles/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE SourceFiles)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

