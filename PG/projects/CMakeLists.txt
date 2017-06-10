cmake_minimum_required(VERSION 2.6)
project(PG)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")

add_definitions(-DSFML_STATIC)

include_directories(
  "../.."
  "../internal/sfml/include"
  "../thirdparty/boost"
)

set(SRCS
  ../../PG/app/GameConstants.h
  ../../PG/app/IAppController.h
  ../../PG/app/IGameController.h
  ../../PG/app/PGAppHost.cpp
  ../../PG/app/PGAppHost.h
  ../../PG/core/MathsUtils.h
  ../../PG/core/PGKeyCode.h
  ../../PG/core/PGRectUtils.cpp
  ../../PG/core/PGRectUtils.h
  ../../PG/core/Point.cpp
  ../../PG/core/Point.h
  ../../PG/core/PointUtils.cpp
  ../../PG/core/PointUtils.h
  ../../PG/core/Rect.h
  ../../PG/core/Size.cpp
  ../../PG/core/Size.h
  ../../PG/core/TileCoord.cpp
  ../../PG/core/TileCoord.h
  ../../PG/core/ValueRange.h
  ../../PG/data/AttributeConstants.cpp
  ../../PG/data/AttributeConstants.h
  ../../PG/data/Attributes.cpp
  ../../PG/data/Attributes.h
  ../../PG/data/DataGrid.cpp
  ../../PG/data/DataGrid.h
  ../../PG/data/DataGridUtils.h
  ../../PG/data/EntityHandle.h
  ../../PG/data/EntityLoader.cpp
  ../../PG/data/EntityLoader.h
  ../../PG/entities/Tile.cpp
  ../../PG/entities/Tile.h
  ../../PG/entities/TilePositionCalculator.cpp
  ../../PG/entities/TilePositionCalculator.h
  ../../PG/graphics/Node.h
  ../../PG/graphics/NodeCreator.h
  ../../PG/graphics/Scene.h
  ../../PG/graphics/TextureMeasurer.cpp
  ../../PG/graphics/TextureMeasurer.h
  ../../PG/graphics/ViewHandle.h
  ../../PG/internal/app/GameConstants.cpp
  ../../PG/internal/graphics/SFMLNode.cpp
  ../../PG/internal/graphics/SFMLNode.h
  ../../PG/internal/graphics/SFMLScene.cpp
  ../../PG/internal/graphics/SFMLScene.h
  ../../PG/internal/graphics/SFMLTextureMeasurer.cpp
  ../../PG/internal/graphics/SFMLTextureMeasurer.h
  ../../PG/internal/graphics/SFMLViewHandle.h
  ../../PG/internal/input/PGKeyCodeUtils.h
  ../../PG/inventory/Inventory.cpp
  ../../PG/inventory/Inventory.h
  ../../PG/inventory/InventoryItem.h
  ../../PG/io/IResourceHandler.h
  ../../PG/menu/MenuLayer.cpp
  ../../PG/menu/MenuLayer.h
  ../../PG/menu/MenuManager.cpp
  ../../PG/menu/MenuManager.h
  ../../PG/menu/MenuNode.cpp
  ../../PG/menu/MenuNode.h
  ../../PG/ui/PGButton.cpp
  ../../PG/ui/PGButton.h
  ../../PG/ui/PGDialog.cpp
  ../../PG/ui/PGDialog.h
  ../../PG/ui/PGUI.cpp
  ../../PG/ui/PGUI.h
  ../../PG/ui/PGUIElement.cpp
  ../../PG/ui/PGUIElement.h
  ../../PG/ui/PGUIMessage.h
  ../../PG/ui/PGUIMessageQueuePoster.cpp
  ../../PG/ui/PGUIMessageQueuePoster.h
  ../../PG/ui/PGUIUtils.cpp
  ../../PG/ui/PGUIUtils.h
  ../../PG/util/JsonUtils.cpp
  ../../PG/util/JsonUtils.h
  ../../PG/util/Logger.cpp
  ../../PG/util/Logger.h
)

add_library(PG STATIC "${SRCS}")
