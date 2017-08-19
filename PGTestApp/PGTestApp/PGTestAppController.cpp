#include "PGTestAppController.h"
#include "TagConstants.h"
#include "MainMenuScene.h"
#include "ButtonsTestScene.h"
#include "AnimationsTestScene.h"
#include "PhysicsTestScene.h"
#include "InventoryTestScene.h"
#include "BarTestScene.h"

#include "PG/app/AppConfiguration.h"
#include "PG/app/IPlatformServices.h"
#include "PG/app/AppHostServices.h"
#include "PG/graphics/View.h"

//--------------------------------------------------------
PGTestAppController::PGTestAppController()
: m_AppHostServices(nullptr),
m_View(nullptr)
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
	m_AppConfig.windowSize = PG::Size(800, 600);
	
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
void PGTestAppController::start(PG::AppHostServices& appHostServices, PG::IView& view)
{
    m_AppHostServices = &appHostServices;
    m_View = &view;
	
	std::unique_ptr<PG::ISceneController> mainMenu(new MainMenuScene(*this));
	m_View->replaceScene(mainMenu);
}

//--------------------------------------------------------
void PGTestAppController::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
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
		case TagConstants::kShowPhysicsTest:
		{
			std::unique_ptr<PG::ISceneController> physicsTest(new PhysicsTestScene(*this));
			m_View->pushScene(physicsTest);
			break;
		}
		case TagConstants::kShowInventoryTest:
		{
			std::unique_ptr<PG::ISceneController> inventoryTest(new InventoryTestScene(*this));
			m_View->pushScene(inventoryTest);
			break;
		}
		case TagConstants::kShowBarTest:
		{
			std::unique_ptr<PG::ISceneController> barTest(new BarTestScene(*this));
			m_View->pushScene(barTest);
			break;
		}
		case TagConstants::kExitApp:
		{
			m_AppHostServices->getPlatformServices().exitApp();
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
