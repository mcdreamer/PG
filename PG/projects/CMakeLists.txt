cmake_minimum_required(VERSION 3.0)
project(PG)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT $ENV{BOOST_DIR})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED)

include_directories(
	"../.."
	"../internal/sfml/include"
	${Boost_INCLUDE_DIRS}
	"../thirdparty/stockpile"
	"../thirdparty/jsoncpp/dist"
)

set(PG_ROOT ../../PG)

set(SRCS
	${PG_ROOT}/animation/AnimationUpdater.cpp
	${PG_ROOT}/animation/AnimationUpdater.h
	${PG_ROOT}/animation/IAnimation.h
	${PG_ROOT}/animation/MoveToAnimation.cpp
	${PG_ROOT}/animation/MoveToAnimation.h
	${PG_ROOT}/animation/TextureAnimation.cpp
	${PG_ROOT}/animation/TextureAnimation.h
	${PG_ROOT}/animation/TextureAnimationDefinition.h
	${PG_ROOT}/animation/TextureAnimationUtils.cpp
	${PG_ROOT}/animation/TextureAnimationUtils.h
	${PG_ROOT}/app/AppConfiguration.h
	${PG_ROOT}/app/AppHostServices.h
	${PG_ROOT}/app/GameConstants.h
	${PG_ROOT}/app/IPlatformServices.h
	${PG_ROOT}/app/IGameController.h
	${PG_ROOT}/app/KeyCodeUtils.cpp
	${PG_ROOT}/app/KeyCodeUtils.h
	${PG_ROOT}/app/PGAppHost.cpp
	${PG_ROOT}/app/PGAppHost.h
	${PG_ROOT}/app/StyleSheet.h
	${PG_ROOT}/console/CommandSetHandle.cpp
	${PG_ROOT}/console/CommandSetHandle.h
	${PG_ROOT}/console/CommandSetRemover.cpp
	${PG_ROOT}/console/CommandSetRemover.h
	${PG_ROOT}/console/ConsoleCommandArgument.h
	${PG_ROOT}/console/ConsoleCommandArgumentType.h
	${PG_ROOT}/console/ConsoleCommandRegistry.cpp
	${PG_ROOT}/console/ConsoleCommandRegistry.h
	${PG_ROOT}/console/ConsoleController.cpp
	${PG_ROOT}/console/ConsoleController.h
	${PG_ROOT}/console/InputParser.cpp
	${PG_ROOT}/console/InputParser.h
	${PG_ROOT}/console/RawConsoleCommand.h
	${PG_ROOT}/core/Colour.cpp
	${PG_ROOT}/core/Colour.h
	${PG_ROOT}/core/MathsUtils.h
	${PG_ROOT}/core/KeyCode.h
	${PG_ROOT}/core/RectUtils.cpp
	${PG_ROOT}/core/RectUtils.h
	${PG_ROOT}/core/Point.cpp
	${PG_ROOT}/core/Point.h
	${PG_ROOT}/core/PointUtils.cpp
	${PG_ROOT}/core/PointUtils.h
	${PG_ROOT}/core/Rect.cpp
	${PG_ROOT}/core/Rect.h
	${PG_ROOT}/core/Size.cpp
	${PG_ROOT}/core/Size.h
	${PG_ROOT}/core/SizeUtils.cpp
	${PG_ROOT}/core/SizeUtils.h
	${PG_ROOT}/core/Colour.cpp
	${PG_ROOT}/core/Colour.h
	${PG_ROOT}/core/TileCoord.cpp
	${PG_ROOT}/core/TileCoord.h
	${PG_ROOT}/core/ValueRange.h
	${PG_ROOT}/data/AttributeConstants.cpp
	${PG_ROOT}/data/AttributeConstants.h
	${PG_ROOT}/data/Attributes.cpp
	${PG_ROOT}/data/Attributes.h
	${PG_ROOT}/data/DataGrid.cpp
	${PG_ROOT}/data/DataGrid.h
	${PG_ROOT}/data/DataGridUtils.h
	${PG_ROOT}/data/EntityHandle.h
	${PG_ROOT}/data/EntityLoader.cpp
	${PG_ROOT}/data/EntityLoader.h
	${PG_ROOT}/data/GeometryLoader.cpp
	${PG_ROOT}/data/GeometryLoader.h
	${PG_ROOT}/entities/Tile.cpp
	${PG_ROOT}/entities/Tile.h
	${PG_ROOT}/entities/TilePositionCalculator.cpp
	${PG_ROOT}/entities/TilePositionCalculator.h
	${PG_ROOT}/graphics/Camera.cpp
	${PG_ROOT}/graphics/Camera.h
	${PG_ROOT}/graphics/Node.h
	${PG_ROOT}/graphics/NodeCreator.h
	${PG_ROOT}/graphics/Scene.h
	${PG_ROOT}/graphics/TextureMeasurer.cpp
	${PG_ROOT}/graphics/TextureMeasurer.h
	${PG_ROOT}/graphics/View.h
	${PG_ROOT}/internal/app/GameConstants.cpp
	${PG_ROOT}/internal/graphics/SFMLNode.cpp
	${PG_ROOT}/internal/graphics/SFMLNode.h
	${PG_ROOT}/internal/graphics/SFMLScene.cpp
	${PG_ROOT}/internal/graphics/SFMLScene.h
	${PG_ROOT}/internal/graphics/SFMLTextureMeasurer.cpp
	${PG_ROOT}/internal/graphics/SFMLTextureMeasurer.h
	${PG_ROOT}/internal/graphics/SFMLView.cpp
	${PG_ROOT}/internal/graphics/SFMLView.h
	${PG_ROOT}/internal/input/KeyCodeUtils.h
	${PG_ROOT}/internal/platform/PileResourceHandler.cpp
	${PG_ROOT}/internal/platform/PileResourceHandler.h
	${PG_ROOT}/internal/platform/ResourceHandler.cpp
	${PG_ROOT}/internal/platform/ResourceHandler.h
	${PG_ROOT}/internal/sound/SFMLSoundController.cpp
	${PG_ROOT}/internal/sound/SFMLSoundController.h
	${PG_ROOT}/internal/ui/Console.cpp
	${PG_ROOT}/internal/ui/Console.h
	${PG_ROOT}/inventory/Inventory.cpp
	${PG_ROOT}/inventory/Inventory.h
	${PG_ROOT}/inventory/InventoryItem.h
	${PG_ROOT}/io/IResourceHandler.h
	${PG_ROOT}/physics/PhysicsBody.cpp
	${PG_ROOT}/physics/PhysicsBody.h
	${PG_ROOT}/physics/PhysicsBodyAndNode.h
	${PG_ROOT}/physics/PhysicsBodyCollection.cpp
	${PG_ROOT}/physics/PhysicsBodyCollection.h
	${PG_ROOT}/physics/PhysicsBodyInputHandler.cpp
	${PG_ROOT}/physics/PhysicsBodyInputHandler.h
	${PG_ROOT}/physics/PhysicsWorld.cpp
	${PG_ROOT}/physics/PhysicsWorld.h
	${PG_ROOT}/physics/PhysicsWorldParams.h
	${PG_ROOT}/sound/ISoundController.h
	${PG_ROOT}/sound/Sound.h
	${PG_ROOT}/sound/SoundID.cpp
	${PG_ROOT}/sound/SoundID.h
	${PG_ROOT}/ui/Bar.cpp
	${PG_ROOT}/ui/Bar.h
	${PG_ROOT}/ui/Button.cpp
	${PG_ROOT}/ui/Button.h
	${PG_ROOT}/ui/Dialog.cpp
	${PG_ROOT}/ui/Dialog.h
	${PG_ROOT}/ui/TagReceiver.h
	${PG_ROOT}/ui/UI.cpp
	${PG_ROOT}/ui/UI.h
	${PG_ROOT}/ui/UIElement.cpp
	${PG_ROOT}/ui/UIElement.h
	${PG_ROOT}/ui/UIMessage.cpp
	${PG_ROOT}/ui/UIMessage.h
	${PG_ROOT}/ui/UIMessageQueuePoster.cpp
	${PG_ROOT}/ui/UIMessageQueuePoster.h
	${PG_ROOT}/ui/UIPositionCalculator.cpp
	${PG_ROOT}/ui/UIPositionCalculator.h
	${PG_ROOT}/ui/UIUtils.cpp
	${PG_ROOT}/ui/UIUtils.h
	${PG_ROOT}/util/JsonUtils.cpp
	${PG_ROOT}/util/JsonUtils.h
	${PG_ROOT}/util/Logger.cpp
	${PG_ROOT}/util/Logger.h
)

if(APPLE)
set(PLATFORM_SRCS
	${PG_ROOT}/internal/platform/MacPlatformServices.mm
	${PG_ROOT}/internal/platform/MacPlatformServices.h
)
endif()

if(WIN32)
set(PLATFORM_SRCS
	${PG_ROOT}/internal/platform/WinPlatformServices.cpp  
	${PG_ROOT}/internal/platform/WinPlatformServices.h
)
endif()

add_library(PG STATIC "${SRCS}" "${PLATFORM_SRCS}")

source_group(TREE ${PG_ROOT}/ FILES ${SRCS};${PLATFORM_SRCS})