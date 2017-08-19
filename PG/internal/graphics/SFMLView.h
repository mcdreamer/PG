#pragma once

#include "PG/graphics/View.h"
#include "PG/graphics/Scene.h"

#include <boost/optional.hpp>

#include <stack>

namespace sf
{
    class RenderWindow;
};

namespace PG {

struct SceneControllerHandle;
class AppHostServices;

namespace Internal {

class SFMLScene;

//--------------------------------------------------------
class SFMLView : public IView
{
public:
    SFMLView(sf::RenderWindow* view,
			 AppHostServices& appHostServices)
    : m_View(view),
	m_AppHostServices(appHostServices)
    {}
	
	virtual SceneControllerHandle	replaceScene(SceneControllerPtr& sceneController) override;
	virtual SceneControllerHandle	pushScene(SceneControllerPtr& sceneController) override;
	virtual void					popScene() override;
	
	virtual SceneControllerHandle	addOverlay(SceneControllerPtr& sceneController)  override;
	virtual void					removeOverlay(const SceneControllerHandle& sceneController) override;
	
	sf::RenderWindow*				getRenderWindow() const { return m_View; }
	IScene*							getCurrentScene() const;
	
	void							updateFinished();
	
private:
	enum class PendingSceneOperationType
	{
		kReplace,
		kPush,
		kPop
	};

    sf::RenderWindow*							m_View;
	std::stack<ScenePtr>						m_SceneStack;
	AppHostServices&							m_AppHostServices;
	
	std::vector<ScenePtr>						m_Overlays;
	
	SceneControllerPtr							m_PendingSceneController;
	boost::optional<PendingSceneOperationType>	m_PendingSceneOperationType;
	
	void										presentPendingSceneIfAny();
	SceneControllerHandle						createAndInitialiseScene(SceneControllerPtr& sceneController);
};

}
}
