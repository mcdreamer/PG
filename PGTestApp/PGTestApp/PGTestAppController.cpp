#include "PGTestAppController.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/graphics/ViewHandle.h"
#include "PG/io/IResourceHandler.h"
#include "PG/ui/PGButton.h"

#include <iostream>

//--------------------------------------------------------
class TestScene : public PG::ISceneCallback, public PG::PGUIElement
{
public:
    //--------------------------------------------------------
    TestScene(PG::IViewHandle& viewHandle, const PG::PGSize& viewSize)
    : m_Scene(PG::SceneCreator::createScene(viewSize.width, viewSize.height))
    {
		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 100), "Test Button", 0));
        m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 200), "Another Test Button", 1));

        m_Scene->presentSceneOnView(viewHandle, this);
        m_Scene->setBackgroundColour(0, 0, 0);
        
        auto n = PG::NodeCreator::createSpriteNode("dialog");
        n->setPosition(PG::PGPoint(500, 400));
        auto dh = m_Scene->addChild(n);
        
        auto colNode = PG::NodeCreator::createColourNode(255, 0, 0, 1, PG::PGSize(100, 50));
        colNode->setPosition(PG::PGPoint(0, 0));
        auto colHandle = dh.node->addChild(colNode);
        
        for (int i = 0; i < 10; i++)
        {
            auto colNode = PG::NodeCreator::createColourNode(255, 0, 0, 1, PG::PGSize(10, 10));
            colNode->setPosition(PG::PGPoint(i * 10, i * 10));
            m_Scene->addChild(colNode);
        }
        
        auto textNode = PG::NodeCreator::createTextNode("OpenSans-Regular", 30);
        textNode->setText("Hello");
        textNode->setColour(0, 255, 255, 1);
        m_Text = colHandle.node->addChild(textNode);
        m_Text.node->setPosition(PG::PGPoint(0, 0));
    }
    
    //--------------------------------------------------------
    virtual void keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods) override
    {
        if (code == PG::PGKeyCode::PGKeyCodeUp)
        {
            m_Text.node->setPosition(PG::PGPoint(m_Text.node->getPosition().x, m_Text.node->getPosition().y - 1));
        }
        else if (code == PG::PGKeyCode::PGKeyCodeDown)
        {
            m_Text.node->setPosition(PG::PGPoint(m_Text.node->getPosition().x, m_Text.node->getPosition().y + 1));
        }
    }

	virtual void init() override {}
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override
	{
        if (tag == 0)
        {
            m_Text.node->setText("Clicked!");
        }
        else if (tag == 1)
        {
            m_Text.node->setText("Another Clicked!");
        }
	}
    
    virtual void clickInWindow(PG::PGPoint pt, bool isRightClick) override {}
    virtual void keyUp(PG::PGKeyCode code) override {}
    virtual void draggedWithOffset(PG::PGPoint pt) override {}
    virtual void mouseMoved(PG::PGPoint pt) override {}
    virtual void update(float dt) override {}
    
private:
    PG::ScenePtr                m_Scene;
    PG::NodeHandle              m_Text;
};

//--------------------------------------------------------
class TextScene : public PG::ISceneCallback, public PG::PGUIElement
{
public:
    //--------------------------------------------------------
    TextScene(PG::IViewHandle& viewHandle, const PG::PGSize& viewSize, ISceneTransitionHelper& transHelper)
    : m_Scene(PG::SceneCreator::createScene(viewSize.width, viewSize.height)),
	m_TransHelper(transHelper)
    {
        m_Scene->presentSceneOnView(viewHandle, this);
        m_Scene->setBackgroundColour(50, 50, 50);
        
        auto textNode = PG::NodeCreator::createTextNode("OpenSans-Regular", 120);
        textNode->setText("Hello");
        textNode->setColour(255, 255, 255, 1);
        textNode->setPosition(PG::PGPoint(viewSize.width / 2.0, viewSize.height / 2.0));
        m_Scene->addChild(textNode);
		
		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(viewSize.width / 2.0, viewSize.height * 0.75), "Go", 1));
    }
	
	virtual void init() override {}
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override
	{
		if (tag == 1)
		{
			m_TransHelper.scheduleScene();
		}
	}
	
	virtual void clickInWindow(PG::PGPoint pt, bool isRightClick) override {}
	virtual void keyUp(PG::PGKeyCode code) override {}
	virtual void keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods) override {}
	virtual void draggedWithOffset(PG::PGPoint pt) override {}
	virtual void mouseMoved(PG::PGPoint pt) override {}
	virtual void update(float dt) override {}
	
private:
	ISceneTransitionHelper&	m_TransHelper;
    PG::ScenePtr			m_Scene;
};

//--------------------------------------------------------
PGTestAppController::PGTestAppController()
: m_AppController(nullptr),
m_ViewHandle(nullptr),
m_ResourceHandler(nullptr),
m_RunNextScene(false)
{}

//--------------------------------------------------------
PGTestAppController::~PGTestAppController()
{}

//--------------------------------------------------------
std::string PGTestAppController::getWindowTitle()
{
    return "PG Test App";
}

//--------------------------------------------------------
PG::PGSize PGTestAppController::getWindowSize()
{
    return PG::PGSize(800, 600);
}

//--------------------------------------------------------
int PGTestAppController::getTileSize()
{
    return 32;
}

//--------------------------------------------------------
void PGTestAppController::start(PG::IAppController& appController,
                                PG::IViewHandle& viewHandle,
                                PG::IResourceHandler& resourceHandler)
{
    m_AppController = &appController;
    m_ViewHandle = &viewHandle;
    m_ResourceHandler = &resourceHandler;
    
    m_SceneCallback.reset(new TextScene(*m_ViewHandle, getWindowSize(), *this));
}

//--------------------------------------------------------
void PGTestAppController::scheduleScene()
{
	m_RunNextScene = true;
}

//--------------------------------------------------------
void PGTestAppController::updateFinished()
{
	if (m_RunNextScene)
	{
		m_SceneCallback.reset(new TestScene(*m_ViewHandle, getWindowSize()));
		
		m_RunNextScene = true;
	}
}
