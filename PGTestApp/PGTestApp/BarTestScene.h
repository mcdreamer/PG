#pragma once

#include "PG/graphics/Scene.h"

#include <memory>

//--------------------------------------------------------
class BarTestScene : public PG::ISceneController
{
	struct GameState;
	
public:
	BarTestScene();
	~BarTestScene();
	
	virtual void initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override {}
	virtual void keyDown(PG::KeyCode code, PG::KeyModifier mods) override {}
	
	virtual void update(double dt) override;
	
	virtual bool receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override;
	
private:
	PG::SceneHandle					m_Scene;
	std::unique_ptr<GameState>		m_GameState;
};
