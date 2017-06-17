#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/PGTagReceiver.h"

//--------------------------------------------------------
class MainMenuScene : public PG::ISceneController, public PG::PGTagReciever
{
public:
	MainMenuScene(PG::PGTagReciever& appTagTarget)
	: m_AppTagTarget(appTagTarget)
	{}
	
	virtual void initScene(PG::SceneHandle scene) override;

	virtual void clickInScene(PG::PGPoint pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::PGPoint pt) override {}
	virtual void mouseMoved(PG::PGPoint pt) override {}
	
	virtual void keyUp(PG::PGKeyCode code) override {}
	virtual void keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods) override {}
	
	virtual void update(float dt) override {}
	
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override;
	
private:
	PG::SceneHandle			m_Scene;
	PGTagReciever&			m_AppTagTarget;
};
