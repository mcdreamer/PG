#pragma once

#include "PG/internal/graphics/SFMLNode.h"
#include "PG/internal/graphics/SFMLViewHandle.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGUI.h"
#include "PG/ui/PGUIElement.h"
#include "PG/app/StyleSheet.h"

#include <SFML/Graphics.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLScene : public IScene, public PG::PGUIElement
{
public:
    //--------------------------------------------------------
    SFMLScene()
    : m_Callback(nullptr)
    {
        m_Root = NodeCreator::createNode();
        m_UI.reset(new PG::PGUI(*this));
    }
    
    //--------------------------------------------------------
    virtual void setBackgroundColour(const Colour& colour) override
    {
        m_BackgroundColour = sf::Color(colour.r, colour.g, colour.b, 1);
    }
    
    //--------------------------------------------------------
    virtual NodeHandle addChild(std::unique_ptr<INode>& node) override
    {
        return m_Root->addChild(node);
    }
    
    //--------------------------------------------------------
    virtual void presentSceneOnView(IViewHandle& viewHandle, ISceneCallback* sceneController) override
    {
        auto* sfmlViewHandle = dynamic_cast<SFMLViewHandle*>(&viewHandle);
		
        if (sfmlViewHandle)
        {
            const auto size = sfmlViewHandle->view->getView().getSize();
            sfmlViewHandle->currentScene = this;
            
            m_SceneSize = PGSize(size.x, size.y);
			m_UI->setStyleSheet(sfmlViewHandle->styleSheet);
            m_Callback = sceneController;
        }
    }
    
    //--------------------------------------------------------
    virtual PGSize getSceneSize() const override
    {
        return PGSize(m_SceneSize.width, m_SceneSize.height);
    }
    
    //--------------------------------------------------------
    virtual PGPoint getWindowPointAsScenePoint(const PGPoint& windowPt, INode* layer) const override
    {
        return windowPt;
    }
	
	//--------------------------------------------------------
	virtual const StyleSheet& getStyleSheet() const override
	{
		return m_UI->getStyleSheet();
	}
	
    virtual void init(const StyleSheet& styleSheet) override {}
    virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override {}
	
	//--------------------------------------------------------
	void clickInWindow(PG::PGPoint pt, bool isRightClick)
    {
        if (!m_UI->handleClick(pt) && m_Callback)
        {
            m_Callback->clickInWindow(pt, isRightClick);
        }
    }
	//--------------------------------------------------------
    virtual void pushUIElement(PGUIElement* uiElement) override
    {
        m_UI->pushElement(uiElement);
    }
    
    //--------------------------------------------------------
    void update(float dt)
    {
        m_UI->update();
    
        if (m_Callback)
        {
            m_Callback->update(dt);
        }
    }
	
	ISceneCallback*				getCallback() { return m_Callback; }
	const NodePtr&				getRoot() const { return m_Root; }
	const sf::Color             getBackgroundColour() const { return m_BackgroundColour; }
	
private:
    PGSize                      m_SceneSize;
    NodePtr                     m_Root;
    ISceneCallback*             m_Callback;
    sf::Color                   m_BackgroundColour;
    std::unique_ptr<PG::PGUI>	m_UI;
};

}
}
