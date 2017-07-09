#include "PhysicsTestScene.h"
#include "TagConstants.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsBodyAndNode.h"
#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"

namespace
{
	//--------------------------------------------------------
	PG::PhysicsWorldParams getWorldParams()
	{
		PG::PhysicsWorldParams params;
		
		params.gravity = PG::	PGSize(0, 100);
		
		return params;
	}
}

//--------------------------------------------------------
struct PhysicsTestScene::PhysicsState : public PG::PhysicsWorldCallback
{
	PhysicsState(const PG::PGRect& bodyRect)
	: world(getWorldParams(), *this), bodyAndNode(bodyRect), levelGeometry(10, 10)
	{}

	PG::PhysicsWorld		world;
	PG::PhysicsBodyAndNode	bodyAndNode;
	PG::DataGrid<bool>		levelGeometry;
	
	//--------------------------------------------------------
	virtual void bodiesDidCollide(const PG::PhysicsBody& bodyOne, const PG::PhysicsBody& bodyTwo) override
	{
	}
};

//--------------------------------------------------------
PhysicsTestScene::PhysicsTestScene(PG::PGTagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget), m_State(new PhysicsState(PG::PGRect(PG::PGPoint(32, 0), PG::PGSize(PG::GameConstants::tileSize(), PG::GameConstants::tileSize()))))
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
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.75), "Back", TagConstants::kPopScene));
	
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
void PhysicsTestScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, tag));
}

//--------------------------------------------------------
void PhysicsTestScene::update(float dt)
{
	m_State->world.applyPhysicsForBody(m_State->bodyAndNode.body, m_State->levelGeometry, dt);
	
	m_State->bodyAndNode.node.node->setPosition(m_State->bodyAndNode.body.bounds.origin);
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
