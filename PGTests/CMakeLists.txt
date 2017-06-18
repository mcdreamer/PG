cmake_minimum_required(VERSION 2.6)
project(PGTests)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")

add_definitions(-DSFML_STATIC)

include_directories(
  "../"
  "../PG/internal/sfml/include"
  "../PG/thirdparty/boost"
  "../PG/thirdparty/googletest/googletest/include"
)

link_directories(
  ""
)

set(SRCS
  PGTests/CoreDataTests.cpp
  PGTests/CoreDataTests.h
  PGTests/GeometryTests.cpp
  PGTests/GeometryTests.h
  PGTests/UITests.cpp
  PGTests/UITests.h
  PGTests/main.cpp
)

add_executable(PGTests "${SRCS}")
