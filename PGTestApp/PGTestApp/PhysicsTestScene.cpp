#include "PhysicsTestScene.h"
#include "TagConstants.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsBodyAndNode.h"
#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBodyCollection.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/BindableValue.h"

namespace
{
	//--------------------------------------------------------
	PG::PhysicsWorldParams getWorldParams()
	{
		PG::PhysicsWorldParams params;
		
		params.gravity = PG::PGSize(0, 1000);
		params.jumpForce = PG::PGPoint(0, -420);
		params.friction = 0.78;
		
		const double speed = 400;
		params.minMovement = PG::PGPoint(-speed, -4850);
		params.maxMovement = PG::PGPoint(speed, 1000);
		
		params.forward = PG::PGPoint(3000, 0);
		
		return params;
	}
}

//--------------------------------------------------------
struct PhysicsTestScene::GameState
{
	GameState()
	: numHearts(0)
	{}

	PG::BindableValue<int> numHearts;
	PG::BindableValue<int> numStars;
};

//--------------------------------------------------------
struct PhysicsTestScene::PhysicsState
{
	PhysicsState(const PG::PGRect& bodyRect)
	: world(getWorldParams()), bodyAndNode(bodyRect), levelGeometry(10, 10)
	{}

	PG::PhysicsWorld			world;
	PG::PhysicsBodyAndNode		bodyAndNode;
	PG::DataGrid<bool>			levelGeometry;
	
	PG::PhysicsBodyCollection	hearts;
	PG::PhysicsBodyCollection	stars;
};

//--------------------------------------------------------
PhysicsTestScene::PhysicsTestScene(PG::PGTagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget),
m_State(new PhysicsState(PG::PGRect(PG::PGPoint(32, 0), PG::PGSize(PG::GameConstants::tileSize(), PG::GameConstants::tileSize())))),
m_GameState(new GameState)
{}

//--------------------------------------------------------
PhysicsTestScene::~PhysicsTestScene()
{
}

//--------------------------------------------------------
void PhysicsTestScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(197, 239, 247));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto ghostNode = PG::NodeCreator::createSpriteNode("ghost");
	m_State->bodyAndNode.node = m_Scene.scene->addChild(ghostNode);
	
	auto heartCountNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 20);
	heartCountNode->setPosition(PG::PGPoint(20, 20));
	heartCountNode->setColour(PG::Colour(255, 0, 0));
	m_HeartCountNode = m_Scene.scene->addChild(heartCountNode);
	PG::UIUtils::bindTextNodeToValue(m_HeartCountNode, m_GameState->numHearts);
	
	auto starsCountNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 20);
	starsCountNode->setPosition(PG::PGPoint(20, 40));
	starsCountNode->setColour(PG::Colour(0, 128, 255));
	m_StarsCountNode = m_Scene.scene->addChild(starsCountNode);
	PG::UIUtils::bindTextNodeToValue(m_StarsCountNode, m_GameState->numStars);
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.75), "Back", TagConstants::kPopScene));
	
	generateAndSetupLevelGeometry();
	generateAndSetupHearts();
	generateAndSetupStars();
}

//--------------------------------------------------------
void PhysicsTestScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, tag));
}

//--------------------------------------------------------
void PhysicsTestScene::update(float dt)
{
	m_State->world.applyPhysicsForBody(m_State->bodyAndNode.body, m_State->levelGeometry, dt);
	
	m_State->bodyAndNode.node.node->setPosition(m_State->bodyAndNode.body.bounds.origin);
	
	m_State->hearts.findCollisionsWithBodyInWorld(m_State->bodyAndNode.body, m_State->world, [this](const int& h) { ++m_GameState->numHearts; });
	m_State->stars.findCollisionsWithBodyInWorld(m_State->bodyAndNode.body, m_State->world, [this](const int& s) { ++m_GameState->numStars; });
}

//--------------------------------------------------------
void PhysicsTestScene::keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods)
{
	PG::PhysicsBodyInputHandler inputHandler(m_State->bodyAndNode.body);
	inputHandler.keyDown(code, mods);
}

//--------------------------------------------------------
void PhysicsTestScene::keyUp(PG::PGKeyCode code)
{
	PG::PhysicsBodyInputHandler inputHandler(m_State->bodyAndNode.body);
	inputHandler.keyUp(code);
}

//--------------------------------------------------------
void PhysicsTestScene::generateAndSetupLevelGeometry()
{
	PG::TilePositionCalculator tilePosCalc;
	
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (y == 9 || (y == 8 && x == 9) || (y == 6 && x == 7))
			{
				m_State->levelGeometry.set(x, y, true);
				
				auto blockNode = PG::NodeCreator::createSpriteNode("block");
				blockNode->setPosition(tilePosCalc.calculatePoint(PG::TileCoord(x, y)));
				m_Scene.scene->addChild(blockNode);
			}
			else
			{
				m_State->levelGeometry.set(x, y, false);
			}
		}
	}
}

//--------------------------------------------------------
void PhysicsTestScene::generateAndSetupHearts()
{
	std::vector<PG::TileCoord> itemCoords = {
		PG::TileCoord(8, 8),
		PG::TileCoord(7, 8),
		PG::TileCoord(1, 6)
	};
	
	generateAndSetupItems(m_State->hearts, itemCoords, "heart");
}

//--------------------------------------------------------
void PhysicsTestScene::generateAndSetupStars()
{
	std::vector<PG::TileCoord> itemCoords = {
		PG::TileCoord(8, 2),
		PG::TileCoord(7, 3),
		PG::TileCoord(1, 4)
	};
	
	generateAndSetupItems(m_State->stars, itemCoords, "star");
}

//--------------------------------------------------------
void PhysicsTestScene::generateAndSetupItems(PG::PhysicsBodyCollection& bodyCollection,
											 const std::vector<PG::TileCoord>& itemCoords,
											 const std::string& spriteName)
{
	PG::TilePositionCalculator tilePosCalc;
	
	for (const auto& itemCoord : itemCoords)
	{
		auto node = PG::NodeCreator::createSpriteNode(spriteName);
		node->setPosition(tilePosCalc.calculatePoint(itemCoord));
		bodyCollection.addItemWithBody(0,
									   m_Scene.scene->addChild(node),
									   PG::PhysicsBody(PG::PGRect(tilePosCalc.calculatePoint(itemCoord), PG::PGSize(PG::GameConstants::tileSize(), PG::GameConstants::tileSize()))));
	}
}
