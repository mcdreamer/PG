#pragma once

#include "PG/graphics/Scene.h"
#include "PG/ui/PGTagReceiver.h"

#include <memory>

namespace PG {
	struct TileCoord;
}

//--------------------------------------------------------
class InventoryTestScene : public PG::ISceneController, public PG::PGTagReciever
{
	struct GameState;
	
public:
	InventoryTestScene(PG::PGTagReciever& appTagTarget);
	~InventoryTestScene();
	
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
	std::unique_ptr<GameState>		m_GameState;
	
	void drawInventoryBackground();
	void updateInventory();
};
