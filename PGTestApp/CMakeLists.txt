cmake_minimum_required(VERSION 3.0)
project(PGTestApp)

set(SNAPPY_BUILD_TESTS OFF CACHE BOOL "")

add_subdirectory("../../PG/PG/projects" "./PG")
add_subdirectory("../../PG/PG/thirdparty/stockpile/stockpile/lib" "./stockpile")
add_subdirectory("../../PG/PG/thirdparty/stockpile/thirdparty/snappy" "./snappy")

include("stockpile_cmake.txt")
include("pg_cmake.txt")

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
  PGTestApp/BarTestScene.cpp
  PGTestApp/BarTestScene.h
  PGTestApp/CameraTestScene.cpp
  PGTestApp/CameraTestScene.h
  PGTestApp/ButtonsTestScene.cpp
  PGTestApp/ButtonsTestScene.h
  PGTestApp/InventoryTestScene.cpp
  PGTestApp/InventoryTestScene.h
  PGTestApp/PhysicsTestScene.cpp
  PGTestApp/PhysicsTestScene.h  
  PGTestApp/SoundTestScene.cpp
  PGTestApp/SoundTestScene.h
  PGTestApp/main.cpp
  PGTestApp/MainMenuScene.cpp
  PGTestApp/MainMenuScene.h
  PGTestApp/PGTestAppController.cpp
  PGTestApp/PGTestAppController.h
  PGTestApp/TagConstants.h
)

set(PILEOUTPUT pgtestapp.pile)

build_pile(../../PG/thirdparty/stockpile/stockpile/tool/build/stockpile
    ../PGTestApp/resources/resources.json
    ../PGTestApp/resources
    ${PILEOUTPUT})

set_source_files_properties(${PILEOUTPUT} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

add_executable(PGTestApp "${SRCS}" ${PILEOUTPUT})

pg_set_app_link_libs()

target_link_libraries(PGTestApp ${APP_LINK_LIBS})

set_target_properties(PGTestApp PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER com.mcdreamer.pgtestapp
)