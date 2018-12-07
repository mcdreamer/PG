#pragma once

#include "PG/internal/graphics/SFMLNode.h"
#include "PG/internal/graphics/SFMLView.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/Camera.h"
#include "PG/app/StyleSheet.h"
#include "PG/animation/IAnimation.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLScene : public IScene
{
public:
    SFMLScene(SceneControllerPtr& controller,
			  const Size& size,
			  const StyleSheet& styleSheet);

	~SFMLScene();
	
	virtual void					pushUIElement(UIElement* uiElement) override;
	virtual UILayer&				getUILayer() override { return *m_UILayer; }
	
    virtual NodeHandle				addChild(std::unique_ptr<INode>& node) override;
	virtual void					setBackgroundColour(const Colour& colour) override;
	virtual void					setCamera(const Camera& camera) override;
	virtual void					addAnimation(std::unique_ptr<IAnimation>& animation) override;
	
	virtual Size					getSceneSize() const override;
	virtual	SceneControllerHandle	getController() const override { return m_SceneController.get(); }
	virtual NodeHandle				getRoot() const override { return m_Root.get(); }
	virtual const Colour			getBackgroundColour() const override { return m_BackgroundColour; }
	virtual Camera					getCamera() const override { return m_Camera; }
	
	virtual void					clickInScene(Point pt, bool isRightClick) override;
    virtual void					update(double dt) override;
	
private:
    Size							m_SceneSize;
    NodePtr							m_Root;
    SceneControllerPtr				m_SceneController;
    Colour							m_BackgroundColour;
	Camera							m_Camera;
	AnimationPtrArray				m_Animations;
	
    std::unique_ptr<UILayer>		m_UILayer;
};

}
}
