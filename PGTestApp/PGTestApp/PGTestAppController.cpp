#include "PGTestAppController.h"
#include "PG/app/AppConfiguration.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/graphics/ViewHandle.h"
#include "PG/io/IResourceHandler.h"
#include "PG/ui/PGButton.h"

#include <iostream>

//--------------------------------------------------------
class ButtonTestScene : public PG::ISceneCallback, public PG::PGUIElement
{
public:
    //--------------------------------------------------------
    ButtonTestScene(PG::IViewHandle& viewHandle)
    : m_Scene(PG::SceneCreator::createScene())
    {
		m_Scene->presentSceneOnView(viewHandle, this);
		m_Scene->setBackgroundColour(PG::Colour(0, 0, 0));

		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 100), "Main Menu", 0));
		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 200), "Test Button", 1));
		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 300), "Another Test Button", 2));
		
        auto textNode = PG::NodeCreator::createTextNode(m_Scene->getStyleSheet().uiFontName, 30);
        textNode->setText("Hello");
        textNode->setColour(PG::Colour(0, 255, 255));
		textNode->setPosition(PG::PGPoint(200, 400));
        m_Text = m_Scene->addChild(textNode);
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

	virtual void init(const PG::StyleSheet& styleSheet) override {}
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override
	{
		switch (tag)
		{
			case 0:
				
				break;
		
			case 1:
				m_Text.node->setText("Clicked!");
				break;

			case 2:
				m_Text.node->setText("Another Clicked!");
				break;
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
class MainMenuScene : public PG::ISceneCallback, public PG::PGUIElement
{
public:
    //--------------------------------------------------------
    MainMenuScene(PG::IViewHandle& viewHandle, ISceneTransitionHelper& transHelper)
    : m_Scene(PG::SceneCreator::createScene()),
	m_TransHelper(transHelper)
    {
        m_Scene->presentSceneOnView(viewHandle, this);
        m_Scene->setBackgroundColour(PG::Colour(5, 0, 161));
		
		const auto sceneSize = m_Scene->getSceneSize();
		
		auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
		logoNode->setPosition(PG::PGPoint(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
		m_Scene->addChild(logoNode);
		
        auto textNode = PG::NodeCreator::createTextNode(m_Scene->getStyleSheet().uiFontName, 120);
        textNode->setText("Test App");
        textNode->setColour(PG::Colour(255, 255, 255));
        textNode->setPosition(PG::PGPoint(sceneSize.width / 2.0, 45 + (textNode->getSize().height / 2.0)));
        m_Scene->addChild(textNode);
		
		m_Scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.75), "Buttons Test", 1));
    }
	
	virtual void init(const PG::StyleSheet& styleSheet) override {}
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
{
	initialiseConfig();
}

//--------------------------------------------------------
PGTestAppController::~PGTestAppController()
{}

//--------------------------------------------------------
void PGTestAppController::initialiseConfig()
{
	m_AppConfig.windowTitle = "PG Test App";
	m_AppConfig.windowSize = PG::PGSize(800, 600);
	
	m_AppConfig.tileSize = 32;
	
	m_AppConfig.styleSheet.uiFontName = "OpenSans-Regular";
	m_AppConfig.styleSheet.buttonBackgroundColour = PG::Colour(150, 150, 200);
	m_AppConfig.styleSheet.buttonTextColour = PG::Colour::white();
	m_AppConfig.styleSheet.buttonPadding = 4;
}

//--------------------------------------------------------
PG::AppConfiguration PGTestAppController::getConfiguration()
{
	return m_AppConfig;
}

//--------------------------------------------------------
void PGTestAppController::start(PG::IAppController& appController,
                                PG::IViewHandle& viewHandle,
                                PG::IResourceHandler& resourceHandler)
{
    m_AppController = &appController;
    m_ViewHandle = &viewHandle;
    m_ResourceHandler = &resourceHandler;
    
    m_SceneCallback.reset(new MainMenuScene(*m_ViewHandle, *this));
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
		m_SceneCallback.reset(new ButtonTestScene(*m_ViewHandle));
		
		m_RunNextScene = false;
	}
}
