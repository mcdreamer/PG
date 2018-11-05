cmake_minimum_required(VERSION 3.0)
project(PGTestApp)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "-std=c++14")

include("pg_cmake.txt")

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

build_pg_app(
  "${SRCS}"
  ../PGTestApp/resources
  resources.json
  PGTestApp
  com.mcdreamer.pgtestapp)
