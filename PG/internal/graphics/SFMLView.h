#pragma once

#include "PG/graphics/View.h"
#include "PG/graphics/Scene.h"
#include "PG/app/StyleSheet.h"

#include <boost/optional.hpp>

#include <stack>

namespace sf
{
    class RenderWindow;
};

namespace PG {

struct SceneControllerHandle;

namespace Internal {

class SFMLScene;

//--------------------------------------------------------
class SFMLView : public IView
{
public:
    SFMLView(sf::RenderWindow* view_,
			 ConsoleController& consoleController,
			 const StyleSheet& styleSheet_)
    : m_View(view_),
	m_ConsoleController(consoleController),
	m_StyleSheet(styleSheet_)
    {}
	
	virtual SceneControllerHandle	replaceScene(SceneControllerPtr& sceneController) override;
	virtual SceneControllerHandle	pushScene(SceneControllerPtr& sceneController) override;
	virtual void					popScene() override;
	
	virtual SceneControllerHandle	addOverlay(SceneControllerPtr& sceneController)  override;
	virtual void					removeOverlay(const SceneControllerHandle& sceneController) override;
	
	sf::RenderWindow*				getRenderWindow() const { return m_View; }
	IScene*							getCurrentScene() const;
	const StyleSheet&				getStyleSheet() const { return m_StyleSheet; }
	
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
	ConsoleController&							m_ConsoleController;
	const StyleSheet							m_StyleSheet;
	
	std::vector<ScenePtr>						m_Overlays;
	
	SceneControllerPtr							m_PendingSceneController;
	boost::optional<PendingSceneOperationType>	m_PendingSceneOperationType;
	
	void										presentPendingSceneIfAny();
	SceneControllerHandle						createAndInitialiseScene(SceneControllerPtr& sceneController);
};

}
}
