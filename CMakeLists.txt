cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

project(rubik-s-cube)

# Qt setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED ENV{QT6_DIR})
  message(FATAL_ERROR "QT6_DIR was not found")
endif()

message(STATUS "Using Qt6: \"$ENV{QT6_DIR}\"")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}$ENV{QT6_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

add_subdirectory(ThirdParty/glm)

add_executable(${PROJECT_NAME}
  SourceFiles/main.cpp
  SourceFiles/core/glbuffer.h
  SourceFiles/core/glbuffer.cpp
  SourceFiles/core/glerror.h
  SourceFiles/core/glerror.cpp
  SourceFiles/core/glprogram.h
  SourceFiles/core/glprogram.cpp
  SourceFiles/core/glshader.h
  SourceFiles/core/glshader.cpp
  SourceFiles/core/glvertex_array.h
  SourceFiles/core/glvertex_array.cpp
  SourceFiles/core/logger.h
  SourceFiles/core/logger.cpp
  SourceFiles/core/triangle_painter.h
  SourceFiles/core/triangle_painter.cpp
  SourceFiles/ui/glview.h
  SourceFiles/ui/glview.cpp
  SourceFiles/ui/main_window.h
  SourceFiles/ui/main_window.cpp
)

add_compile_definitions(GL_SILENCE_DEPRECATION)

target_include_directories(${PROJECT_NAME} PRIVATE SourceFiles)

target_link_libraries(
  ${PROJECT_NAME}
  Qt6::Widgets
  Qt6::OpenGLWidgets
  glm
)
