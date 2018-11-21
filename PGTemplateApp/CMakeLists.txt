cmake_minimum_required(VERSION 3.0)
project(PGTemplateApp)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("../PG/projects/pg_cmake.txt")

set(SRCS
  PGTemplateApp/main.cpp
  PGTemplateApp/MainMenuScene.cpp
  PGTemplateApp/MainMenuScene.h
  PGTemplateApp/AppController.cpp
  PGTemplateApp/AppController.h
)

build_pg_app(
  "${SRCS}"
  ../PGTemplateApp/resources
  resources.json
  PGTemplateApp
  com.mcdreamer.pgtemplateapp
  ../PGTemplateApp/Info.plist)
