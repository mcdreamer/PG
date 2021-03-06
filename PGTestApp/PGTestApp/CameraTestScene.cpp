#include "CameraTestScene.h"
#include "CameraTestScene.h"
#include "TagConstants.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsBodyAndNode.h"
#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBodyCollection.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/graphics/Camera.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/ui/UI.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"
#include "PG/app/AppHostServices.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/BindableValue.h"

#include <iostream>

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
struct CameraTestScene::PhysicsState
{
	PhysicsState(const PG::Rect& bodyRect)
	: world(getWorldParams()), bodyAndNode(bodyRect), levelGeometry(100, 10)
	{}
	
	PG::PhysicsWorld			world;
	PG::PhysicsBodyAndNode		bodyAndNode;
	PG::DataGrid<bool>			levelGeometry;
};

//--------------------------------------------------------
CameraTestScene::CameraTestScene()
: m_State(new PhysicsState(PG::Rect(PG::Point(32, 0), PG::Size(PG::GameConstants::tileSize(), PG::GameConstants::tileSize()))))
{}

//--------------------------------------------------------
CameraTestScene::~CameraTestScene()
{
}

//--------------------------------------------------------
void CameraTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(197, 239, 247));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto ghostNode = PG::NodeCreator::createSpriteNode("ghost");
	m_State->bodyAndNode.node = m_Scene.scene->addChild(ghostNode);
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	
	auto& ui = m_Scene.scene->getUILayer();
	ui.pushElement(new PG::Button(uiPosCalc.fromBottomLeftCorner(PG::Size(50, 30)), "Back", TagConstants::kPopScene));
	
	const PG::Camera camera(PG::Size(0.3, 0.1), m_State->bodyAndNode.node);
	m_Scene.scene->setCamera(camera);
	
	generateAndSetupLevelGeometry();
}

//--------------------------------------------------------
void CameraTestScene::update(double dt)
{
	m_State->world.applyPhysicsForBody(m_State->bodyAndNode.body, m_State->levelGeometry, dt);
	
	m_State->bodyAndNode.node.node->setPosition(m_State->bodyAndNode.body.bounds.origin);
}

//--------------------------------------------------------
void CameraTestScene::keyDown(PG::KeyCode code, PG::KeyModifier mods)
{
	PG::PhysicsBodyInputHandler inputHandler(m_State->bodyAndNode.body);
	inputHandler.keyDown(code, mods);
}

//--------------------------------------------------------
void CameraTestScene::keyUp(PG::KeyCode code)
{
	PG::PhysicsBodyInputHandler inputHandler(m_State->bodyAndNode.body);
	inputHandler.keyUp(code);
}

//--------------------------------------------------------
void CameraTestScene::generateAndSetupLevelGeometry()
{
	PG::TilePositionCalculator tilePosCalc;
	
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 100; ++x)
		{
			if (y == 9 || (y == 8 && (x % 10) == 0))
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

