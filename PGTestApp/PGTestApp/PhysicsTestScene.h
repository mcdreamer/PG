#pragma once

#include "PG/graphics/Node.h"
#include "PG/graphics/Scene.h"

#include <memory>

namespace PG {
class PhysicsBodyCollection;
struct TileCoord;
}

//--------------------------------------------------------
class PhysicsTestScene : public PG::ISceneController
{
	struct PhysicsState;
	struct GameState;
	
public:
	PhysicsTestScene();
	~PhysicsTestScene();
	
	virtual void initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override;
	virtual void keyDown(PG::KeyCode code, PG::KeyModifier mods) override;
	
	virtual void update(double dt) override;
	
private:
	PG::SceneHandle					m_Scene;
	PG::NodeHandle					m_HeartCountNode;
	PG::NodeHandle					m_StarsCountNode;
	std::unique_ptr<PhysicsState>	m_State;
	std::unique_ptr<GameState>		m_GameState;
	
	void generateAndSetupLevelGeometry();
	void generateAndSetupHearts();
	void generateAndSetupStars();
	void generateAndSetupItems(PG::PhysicsBodyCollection& bodyCollection,
							   const std::vector<PG::TileCoord>& itemCoords,
							   const std::string& spriteName);
};
