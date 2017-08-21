#pragma once

#include "PG/internal/graphics/SFMLNode.h"
#include "PG/internal/graphics/SFMLView.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/UI.h"
#include "PG/ui/TagReceiver.h"
#include "PG/app/StyleSheet.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLScene : public IScene, public PG::TagReciever
{
public:
    SFMLScene(SceneControllerPtr& controller,
			  const Size& size,
			  const StyleSheet& styleSheet);
	
    virtual NodeHandle				addChild(std::unique_ptr<INode>& node) override;
	virtual	void					pushUIElement(UIElement* uiElement) override;
	virtual void					setBackgroundColour(const Colour& colour) override;
	
	virtual Size					getSceneSize() const override;
	virtual	SceneControllerHandle	getController() const override { return m_SceneController.get(); }
	virtual NodeHandle				getRoot() const override { return m_Root.get(); }
	virtual NodeHandle				getUIRoot() const override { return m_UIRoot.get(); }
	virtual const Colour			getBackgroundColour() const override { return m_BackgroundColour; }
	virtual Point					getWindowPointAsScenePoint(const Point& windowPt, INode* layer) const override;
	
    virtual void					receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override {}
	
	virtual void					clickInScene(PG::Point pt, bool isRightClick) override;
    virtual void					update(double dt) override;
	
private:
    Size							m_SceneSize;
    NodePtr							m_Root;
	NodePtr							m_UIRoot;
    SceneControllerPtr				m_SceneController;
    Colour							m_BackgroundColour;
    std::unique_ptr<PG::UI>			m_UI;
};

}
}
