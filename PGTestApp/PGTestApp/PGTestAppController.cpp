#include "PGTestAppController.h"
#include "TagConstants.h"
#include "MainMenuScene.h"
#include "ButtonsTestScene.h"
#include "AnimationsTestScene.h"

#include "PG/app/AppConfiguration.h"
#include "PG/app/IPlatformServices.h"
#include "PG/graphics/View.h"

//--------------------------------------------------------
PGTestAppController::PGTestAppController()
: m_PlatformServices(nullptr),
m_View(nullptr),
m_ResourceHandler(nullptr)
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
	m_AppConfig.styleSheet.buttonPadding = 8;
}

//--------------------------------------------------------
PG::AppConfiguration PGTestAppController::getConfiguration()
{
	return m_AppConfig;
}

//--------------------------------------------------------
void PGTestAppController::start(PG::IPlatformServices& platformServices,
                                PG::IView& view,
                                PG::IResourceHandler& resourceHandler)
{
    m_PlatformServices = &platformServices;
    m_View = &view;
    m_ResourceHandler = &resourceHandler;
	
	std::unique_ptr<PG::ISceneController> mainMenu(new MainMenuScene(*this));
	m_View->replaceScene(mainMenu);
}

//--------------------------------------------------------
void PGTestAppController::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case TagConstants::kPopScene:
		{
			m_View->popScene();
			break;
		}
		case TagConstants::kShowButtonsTest:
		{
			std::unique_ptr<PG::ISceneController> buttonTest(new ButtonTestScene(*this));
			m_View->pushScene(buttonTest);
			break;
		}
		case TagConstants::kShowAnimationsTest:
		{
			std::unique_ptr<PG::ISceneController> animationsTest(new AnimationsTestScene(*this));
			m_View->pushScene(animationsTest);
			break;
		}
		case TagConstants::kExitApp:
		{
			m_PlatformServices->exitApp();
			break;
		}
		default:
			break;
	}
}

//--------------------------------------------------------
void PGTestAppController::updateFinished()
{
}
