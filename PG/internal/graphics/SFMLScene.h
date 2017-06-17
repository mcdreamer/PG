#pragma once

#include "PG/internal/graphics/SFMLNode.h"
#include "PG/internal/graphics/SFMLView.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGUI.h"
#include "PG/ui/PGTagReceiver.h"
#include "PG/app/StyleSheet.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLScene : public IScene, public PG::PGTagReciever
{
public:
    SFMLScene(SceneControllerPtr& controller, const PGSize& size, const StyleSheet& styleSheet);
	
    virtual NodeHandle				addChild(std::unique_ptr<INode>& node) override;
	virtual	void					pushUIElement(PGUIElement* uiElement) override;
	virtual void					setBackgroundColour(const Colour& colour) override;
	
	virtual PGSize					getSceneSize() const override;
	virtual const StyleSheet&		getStyleSheet() const override;
	virtual	SceneControllerHandle	getController() const override { return m_SceneController.get(); }
	virtual NodeHandle				getRoot() const override { return m_Root.get(); }
	virtual const Colour			getBackgroundColour() const override { return m_BackgroundColour; }
	virtual PGPoint					getWindowPointAsScenePoint(const PGPoint& windowPt, INode* layer) const override;
	
    virtual void					receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override {}
	
	virtual void					clickInScene(PG::PGPoint pt, bool isRightClick) override;
    virtual void					update(float dt) override;
	
private:
    PGSize							m_SceneSize;
    NodePtr							m_Root;
    SceneControllerPtr				m_SceneController;
    Colour							m_BackgroundColour;
    std::unique_ptr<PG::PGUI>		m_UI;
};

}
}
