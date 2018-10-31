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

file(GLOB RESOURCES_FONTS "PGTestApp/resources/fonts/*")
file(GLOB RESOURCES_IMAGES "PGTestApp/resources/images/*")
file(GLOB RESOURCES_SOUNDS "PGTestApp/resources/sounds/*")

set_source_files_properties(${RESOURCES_FONTS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
set_source_files_properties(${RESOURCES_IMAGES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
set_source_files_properties(${RESOURCES_SOUNDS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

add_executable(PGTestApp "${SRCS}" ${RESOURCES_FONTS} ${RESOURCES_IMAGES} ${RESOURCES_SOUNDS})

find_library(SFMLAUDIO sfml-audio)
if (NOT SFMLAUDIO)
    message(FATAL_ERROR "sfml-audio not found")
endif()

find_library(SFMLSYSTEM sfml-system)
if (NOT SFMLSYSTEM)
    message(FATAL_ERROR "sfml-system not found")
endif()

find_library(SFMLGRAPHICS sfml-graphics)
if (NOT SFMLGRAPHICS)
    message(FATAL_ERROR "sfml-graphics not found")
endif()

find_library(SFMLWINDOW sfml-window)
if (NOT SFMLWINDOW)
    message(FATAL_ERROR "sfml-window not found")
endif()

target_link_libraries(PGTestApp PG ${SFMLAUDIO} ${SFMLSYSTEM} ${SFMLGRAPHICS} ${SFMLWINDOW} "-framework Foundation" "-framework Cocoa" objc)

set_target_properties(PGTestApp PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER com.mcdreamer.pgtestapp
)