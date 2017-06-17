#pragma once

#include "PG/graphics/View.h"
#include "PG/graphics/Scene.h"
#include "PG/app/StyleSheet.h"

namespace sf
{
    class RenderWindow;
};

namespace PG {
namespace Internal {

class SFMLScene;

//--------------------------------------------------------
class SFMLView : public IView
{
public:
    SFMLView(sf::RenderWindow* view_, const StyleSheet& styleSheet_)
    : m_View(view_), m_StyleSheet(styleSheet_)
    {}
	
	virtual SceneControllerHandle	presentScene(SceneControllerPtr& sceneController) override;
	
	sf::RenderWindow*				getRenderWindow() const { return m_View; }
	IScene*							getCurrentScene() const { return m_CurrentScene.get(); }
	const StyleSheet&				getStyleSheet() const { return m_StyleSheet; }
	
	void							updateFinished();
	
private:
    sf::RenderWindow*				m_View;
	SceneControllerPtr				m_PendingSceneController;
    ScenePtr						m_CurrentScene;
	const StyleSheet				m_StyleSheet;
	
	void							presentPendingSceneIfAny();
};

}
}
