#pragma once

#include "PG/graphics/Node.h"
#include "PG/graphics/Scene.h"

#include <memory>

namespace PG {
	class PhysicsBodyCollection;
	struct TileCoord;
}

//--------------------------------------------------------
class CameraTestScene : public PG::ISceneController
{
	struct PhysicsState;
	
public:
	CameraTestScene();
	~CameraTestScene();
	
	virtual void initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override;
	virtual void keyDown(PG::KeyCode code, PG::KeyModifier mods) override;
	
	virtual void update(double dt) override;
	
private:
	PG::SceneHandle					m_Scene;
	std::unique_ptr<PhysicsState>	m_State;
	
	void generateAndSetupLevelGeometry();
};
