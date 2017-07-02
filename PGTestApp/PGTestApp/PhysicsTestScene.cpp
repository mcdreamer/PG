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
: m_AppTagTarget(appTagTarget), m_State(new PhysicsState(PG::PGRect(PG::PGPoint(100, 200), PG::PGSize(PG::GameConstants::tileSize(), PG::GameConstants::tileSize()))))
{}

//--------------------------------------------------------
PhysicsTestScene::~PhysicsTestScene()
{
}

//--------------------------------------------------------
void PhysicsTestScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(161, 5, 5));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
	logoNode->setPosition(PG::PGPoint(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
	m_State->logoHandle = m_Scene.scene->addChild(logoNode);
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.75), "Back", TagConstants::kPopScene));
	
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			m_State->levelGeometry.set(x, y, y == 9);
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
