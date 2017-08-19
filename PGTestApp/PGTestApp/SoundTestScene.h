#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/TagReceiver.h"

#include <memory>

namespace PG {

class AppHostServices;

}

//--------------------------------------------------------
class SoundTestScene : public PG::ISceneController, public PG::TagReciever
{
	struct GameState;
	
public:
	SoundTestScene(PG::TagReciever& appTagTarget);
	~SoundTestScene();
	
	virtual void initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene) override;
	
	virtual void clickInScene(PG::Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(PG::Point pt) override {}
	virtual void mouseMoved(PG::Point pt) override {}
	
	virtual void keyUp(PG::KeyCode code) override {}
	virtual void keyDown(PG::KeyCode code, PG::KeyModifier mods) override {}
	
	virtual void update(double dt) override {}
	
	virtual void receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override;
	
private:
	PG::SceneHandle					m_Scene;
	PG::AppHostServices*			m_AppHostServices;
	TagReciever&					m_AppTagTarget;
	std::unique_ptr<GameState>		m_GameState;
};
