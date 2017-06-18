cmake_minimum_required(VERSION 2.6)
project(PGTestApp)

cmake_policy(SET CMP0015 NEW)

add_subdirectory("../../PG/PG/projects" "./PG")

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")

add_definitions(-DSFML_STATIC)

include_directories(
  "../"
  "../PG/internal/sfml/include"
  "../PG/thirdparty/boost"
)

set(SRCS
  PGTestApp/AnimationsTestScene.cpp
  PGTestApp/AnimationsTestScene.h
  PGTestApp/ButtonsTestScene.cpp
  PGTestApp/ButtonsTestScene.h
  PGTestApp/main.mm
  PGTestApp/MainMenuScene.cpp
  PGTestApp/MainMenuScene.h
  PGTestApp/PGTestAppController.cpp
  PGTestApp/PGTestAppController.h
  PGTestApp/TagConstants.h
)

add_executable(PGTestApp "${SRCS}")

find_library(sfml-graphics libsfml-graphics-s.a "${PROJECT_SOURCE_DIR}/../PG/internal/sfml/lib")
find_library(sfml-window libsfml-window-s.a "${PROJECT_SOURCE_DIR}/../PG/internal/sfml/lib")
find_library(sfml-system libsfml-system-s.a "${PROJECT_SOURCE_DIR}/../PG/internal/sfml/lib")
target_link_libraries(PGTestApp PG ${sfml-system} ${sfml-window} ${sfml-graphics} GL GLU GLX Xrandr X11 xcb freetype jpeg pthread)
