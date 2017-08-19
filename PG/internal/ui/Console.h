#pragma once

#include "PG/graphics/Node.h"
#include "PG/graphics/Scene.h"
#include "PG/ui/TagReceiver.h"

#include <memory>

namespace PG {

class AppHostServices;

namespace Internal {

//--------------------------------------------------------
class ConsoleScene : public ISceneController, public TagReciever
{
	struct State;
	
public:
	ConsoleScene();
	~ConsoleScene();
	
	virtual void initScene(AppHostServices& appHostServices, SceneHandle scene) override;
	
	virtual void clickInScene(Point pt, bool isRightClick) override {}
	virtual void draggedWithOffset(Point pt) override {}
	virtual void mouseMoved(Point pt) override {}
	
	virtual void keyUp(KeyCode code) override {}
	virtual void keyDown(KeyCode code, KeyModifier mods) override;
	
	virtual void update(double dt) override {}
	
	virtual void receiveTag(const int tag, UIMessageQueuePoster& msgPoster) override {}
	
private:
	SceneHandle				m_Scene;
	AppHostServices*		m_AppHostServices;
	std::unique_ptr<State>	m_State;
	
	void createConsoleOutlineLinesNodes(const std::vector<Point>& linePositions,
										const int numOutputLines,
										const int sizePerLine);
	
	void updateOutput();
};

}
}
