cmake_minimum_required(VERSION 2.6)
project(PGTestApp)

add_subdirectory("../../PG/PG/projects" "./PG")

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14")

include_directories(
  "../"
  "../PG/thirdparty/boost"
)

set(SRCS
  PGTestApp/AnimationsTestScene.cpp
  PGTestApp/AnimationsTestScene.h
  PGTestApp/ButtonsTestScene.cpp
  PGTestApp/ButtonsTestScene.h
  PGTestApp/main.cpp
  PGTestApp/MainMenuScene.cpp
  PGTestApp/MainMenuScene.h
  PGTestApp/PGTestAppController.cpp
  PGTestApp/PGTestAppController.h
  PGTestApp/TagConstants.h
)

add_executable(PGTestApp "${SRCS}")

target_link_libraries(PGTestApp PG sfml-system sfml-graphics sfml-window)

file(GLOB RESOURCES_FONTS "PGTestApp/resources/fonts/*")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources/fonts")
file(COPY ${RESOURCES_FONTS} DESTINATION "${CMAKE_BINARY_DIR}/resources/fonts/")

file(GLOB RESOURCES_IMAGES "PGTestApp/resources/images/*")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources/images")
file(COPY ${RESOURCES_IMAGES} DESTINATION "${CMAKE_BINARY_DIR}/resources/images/")

file(GLOB RESOURCES_DATA "PGTestApp/resources/data/*")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources/data")
file(COPY ${RESOURCES_DATA} DESTINATION "${CMAKE_BINARY_DIR}/resources/data/")
