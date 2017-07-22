#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/TagReceiver.h"
#include "PG/animation/MoveToAnimation.h"

//--------------------------------------------------------
class AnimationsTestScene : public PG::ISceneController, public PG::TagReciever
{
public:
	AnimationsTestScene(PG::TagReciever& appTagTarget)
	: m_AppTagTarget(appTagTarget)
	{}
	
	virtual void initScene(PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override {}
	virtual void keyDown(PG::KeyCode code, PG::PGKeyModifier mods) override {}
	
	virtual void update(float dt) override;
	
	virtual void receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override;
	
private:
	PG::SceneHandle			m_Scene;
	TagReciever&			m_AppTagTarget;
	PG::AnimationPtrArray	m_Animations;
};
