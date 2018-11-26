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
class UI;

namespace Internal {

class SFMLScene;

//--------------------------------------------------------
class SFMLView : public IView
{
public:
	SFMLView(sf::RenderWindow* view,
			 AppHostServices& appHostServices);
	~SFMLView();
	
	virtual SceneControllerHandle	replaceScene(SceneControllerPtr& sceneController) override;
	virtual SceneControllerHandle	pushScene(SceneControllerPtr& sceneController) override;
	virtual void					popScene() override;
	
	virtual SceneControllerHandle	addOverlay(SceneControllerPtr& sceneController)  override;
	virtual void					removeOverlay(const SceneControllerHandle& sceneController) override;
	
	virtual void 					clickInView(Point pt, bool isRightClick) override;
	virtual void					update(double dt) override;
	
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
	
	std::unique_ptr<UI>							m_UI;
	
	std::vector<ScenePtr>						m_Overlays;
	
	SceneControllerPtr							m_PendingSceneController;
	boost::optional<PendingSceneOperationType>	m_PendingSceneOperationType;
	
	void										presentPendingSceneIfAny();
	SceneControllerHandle						createAndInitialiseScene(SceneControllerPtr& sceneController);
};

}
}
