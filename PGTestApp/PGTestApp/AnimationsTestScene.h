#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/TagReceiver.h"

//--------------------------------------------------------
class AnimationsTestScene : public PG::ISceneController, public PG::TagReceiver
{
public:
	virtual void initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override {}
	virtual void keyDown(PG::KeyCode code, PG::KeyModifier mods) override {}
	
	virtual void update(double dt) override;
	
private:
	PG::SceneHandle			m_Scene;
};
