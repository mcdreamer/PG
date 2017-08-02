#include "PhysicsTestScene.h"
#include "TagConstants.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsBodyAndNode.h"
#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBodyCollection.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
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
		
		params.gravity = PG::Size(0, 1000);
		params.jumpForce = PG::Point(0, -420);
		params.friction = 0.78;
		
		const double speed = 400;
		params.minMovement = PG::Point(-speed, -4850);
		params.maxMovement = PG::Point(speed, 1000);
		
		params.forward = PG::Point(3000, 0);
		
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
	
	PG::BindableValue<std::string> value;
};

//--------------------------------------------------------
struct PhysicsTestScene::PhysicsState
{
	PhysicsState(const PG::Rect& bodyRect)
	: world(getWorldParams()), bodyAndNode(bodyRect), levelGeometry(10, 10)
	{}

	PG::PhysicsWorld			world;
	PG::PhysicsBodyAndNode		bodyAndNode;
	PG::DataGrid<bool>			levelGeometry;
	
	PG::PhysicsBodyCollection	hearts;
	PG::PhysicsBodyCollection	stars;
};

//--------------------------------------------------------
PhysicsTestScene::PhysicsTestScene(PG::TagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget),
m_State(new PhysicsState(PG::Rect(PG::Point(32, 0), PG::Size(PG::GameConstants::tileSize(), PG::GameConstants::tileSize())))),
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
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	
	PG::UIUtils::createTextNodeForValue(PG::Point(20, 20), PG::Colour(255, 0, 0), 20, m_HeartCountNode, m_Scene, m_GameState->numHearts);
	PG::UIUtils::createTextNodeForValue(PG::Point(20, 40), PG::Colour(0, 128, 255), 20, m_StarsCountNode, m_Scene, m_GameState->numStars);
	
	PG::UIUtils::createTextNodeForValue(PG::Point(20, 60), PG::Colour(0, 0, 0), 20, m_LabelNode, m_Scene, m_GameState->value);
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, uiPosCalc.fromBottomMid(PG::Size(0, sceneSize.height * 0.25)), "Back", TagConstants::kPopScene));
	
	generateAndSetupLevelGeometry();
	generateAndSetupHearts();
	generateAndSetupStars();
}

//--------------------------------------------------------
void PhysicsTestScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::UIMessage::sendTag(&m_AppTagTarget, tag));
}

//--------------------------------------------------------
void PhysicsTestScene::update(float dt)
{
	m_State->world.applyPhysicsForBody(m_State->bodyAndNode.body, m_State->levelGeometry, dt);
	
	m_State->bodyAndNode.node.node->setPosition(m_State->bodyAndNode.body.bounds.origin);
	
	m_State->hearts.findCollisionsWithBodyInWorld(m_State->bodyAndNode.body, m_State->world, [this](const int& h) { ++m_GameState->numHearts; });
	m_State->stars.findCollisionsWithBodyInWorld(m_State->bodyAndNode.body, m_State->world, [this](const int& s) { ++m_GameState->numStars; });
}

namespace
{
	//--------------------------------------------------------
	void addCharacterForKeyCode(const PG::KeyCode& code,
								std::string& str)
	{
		switch (code)
		{
			case PG::KeyCode::kA: str += "a"; break;
			case PG::KeyCode::kB: str += "b"; break;
			case PG::KeyCode::kC: str += "c"; break;
			case PG::KeyCode::kD: str += "d"; break;
			case PG::KeyCode::kE: str += "e"; break;
			case PG::KeyCode::kF: str += "f"; break;
			case PG::KeyCode::kG: str += "g"; break;
			case PG::KeyCode::kH: str += "h"; break;
			case PG::KeyCode::kI: str += "i"; break;
			case PG::KeyCode::kJ: str += "j"; break;
			case PG::KeyCode::kK: str += "k"; break;
			case PG::KeyCode::kL: str += "l"; break;
			case PG::KeyCode::kM: str += "m"; break;
			case PG::KeyCode::kN: str += "n"; break;
			case PG::KeyCode::kO: str += "o"; break;
			case PG::KeyCode::kP: str += "p"; break;
			case PG::KeyCode::kQ: str += "q"; break;
			case PG::KeyCode::kR: str += "r"; break;
			case PG::KeyCode::kS: str += "s"; break;
			case PG::KeyCode::kT: str += "t"; break;
			case PG::KeyCode::kU: str += "u"; break;
			case PG::KeyCode::kV: str += "v"; break;
			case PG::KeyCode::kW: str += "w"; break;
			case PG::KeyCode::kX: str += "x"; break;
			case PG::KeyCode::kY: str += "y"; break;
			case PG::KeyCode::kZ: str += "z"; break;
				
			default:
				break;
		}
	}

	//--------------------------------------------------------
	void handleBackspace(const PG::KeyCode& code,
						 std::string& str)
	{
		if (code == PG::KeyCode::kBackspace && !str.empty())
		{
			str.pop_back();
		}
	}
}

//--------------------------------------------------------
void PhysicsTestScene::keyDown(PG::KeyCode code, PG::KeyModifier mods)
{
	PG::PhysicsBodyInputHandler inputHandler(m_State->bodyAndNode.body);
	inputHandler.keyDown(code, mods);
	
	auto existingValue = m_GameState->value.get();
	addCharacterForKeyCode(code, existingValue);
	handleBackspace(code, existingValue);
	m_GameState->value.set(existingValue);
}

//--------------------------------------------------------
void PhysicsTestScene::keyUp(PG::KeyCode code)
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
									   PG::PhysicsBody(PG::Rect(tilePosCalc.calculatePoint(itemCoord), PG::Size(PG::GameConstants::tileSize(), PG::GameConstants::tileSize()))));
	}
}
