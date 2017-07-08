#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/PGTagReceiver.h"

#include <memory>

//--------------------------------------------------------
class PhysicsTestScene : public PG::ISceneController, public PG::PGTagReciever
{
	struct PhysicsState;
	
public:
	PhysicsTestScene(PG::PGTagReciever& appTagTarget);
	~PhysicsTestScene();
	
	virtual void initScene(PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::PGPoint pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::PGPoint pt) override {}
	virtual void mouseMoved(PG::PGPoint pt) override {}
	
	virtual void keyUp(PG::PGKeyCode code) override;
	virtual void keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods) override;
	
	virtual void update(float dt) override;
	
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override;
	
private:
	PG::SceneHandle					m_Scene;
	PGTagReciever&					m_AppTagTarget;
	std::unique_ptr<PhysicsState>	m_State;
};
