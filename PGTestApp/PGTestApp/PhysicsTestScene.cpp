#include "PhysicsTestScene.h"
#include "TagConstants.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"

//--------------------------------------------------------
struct PhysicsTestScene::PhysicsState : public PG::PhysicsWorldCallback
{
	PhysicsState(const PG::PGRect& bodyRect)
	: world(PG::PGSize(0, 10), *this), body(bodyRect), levelGeometry(10, 10)
	{}

	PG::PhysicsWorld world;
	PG::PhysicsBody body;
	PG::DataGrid<bool> levelGeometry;
	PG::NodeHandle logoHandle;
	
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
	m_State->logoHandle = m_Scene.scene->addChild(ghostNode);
	
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
	m_State->body.updateInWorld(m_State->world, dt);
	
	m_State->world.applyPhysicsForBody(m_State->body, m_State->levelGeometry);
	
	m_State->logoHandle.node->setPosition(m_State->body.bounds.origin);
}

//--------------------------------------------------------
void PhysicsTestScene::keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods)
{
	if (code == PG::PGKeyCodeRight)
	{
		m_State->body.movingRight = true;
	}
	else if (code == PG::PGKeyCodeLeft)
	{
		m_State->body.movingLeft = true;
	}
	else if (code == PG::PGKeyCodeUp)
	{
		m_State->body.jumpToConsume = true;
	}
}

//--------------------------------------------------------
void PhysicsTestScene::keyUp(PG::PGKeyCode code)
{
	if (code == PG::PGKeyCodeRight)
	{
		m_State->body.movingRight = false;
	}
	else if (code == PG::PGKeyCodeLeft)
	{
		m_State->body.movingLeft = false;
	}
}
