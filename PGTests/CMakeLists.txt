cmake_minimum_required(VERSION 3.0)
project(PGTests)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SNAPPY_BUILD_TESTS OFF CACHE BOOL "")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("../PG/projects" "./PG")
add_subdirectory("../PG/thirdparty/googletest/googletest" "thirdparty/googletest")

include("../PG/projects/pg_cmake.txt")

set(BOOST_ROOT $ENV{BOOST_DIR})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS filesystem system REQUIRED)

include_directories(
  "../"
  "../PG/internal/sfml/include"
  ${Boost_INCLUDE_DIRS}
  "../PG/thirdparty/googletest/googletest/include"
)

set(SRCS
  PGTests/CoreDataTests.cpp
  PGTests/CoreDataTests.h
  PGTests/GeometryTests.cpp
  PGTests/GeometryTests.h
  PGTests/UITests.cpp
  PGTests/UITests.h
  PGTests/PhysicsTests.cpp
  PGTests/PhysicsTests.h
  PGTests/main.cpp
)

pg_setup()
pg_set_app_link_libs()

add_executable(PGTests "${INTERNAL_CPP}" "${SRCS}")

target_link_libraries(PGTests ${INTERNAL_LINK_LIBS} ${Boost_LIBRARIES} PG gtest gtest_main)

file(COPY "PGTests/testdata.json" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "PGTests/testgeometry.geometry" DESTINATION "${CMAKE_BINARY_DIR}")