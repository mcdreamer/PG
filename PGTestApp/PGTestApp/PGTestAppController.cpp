#include "PGTestAppController.h"
#include "TagConstants.h"
#include "MainMenuScene.h"
#include "ButtonsTestScene.h"
#include "AnimationsTestScene.h"
#include "PhysicsTestScene.h"
#include "InventoryTestScene.h"
#include "BarTestScene.h"
#include "SoundTestScene.h"
#include "CameraTestScene.h"

#include "PG/app/AppConfiguration.h"
#include "PG/app/IPlatformServices.h"
#include "PG/app/AppHostServices.h"
#include "PG/graphics/View.h"

//--------------------------------------------------------
PGTestAppController::PGTestAppController()
: m_AppHostServices(nullptr),
m_View(nullptr),
m_AppConfig(this)
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
	
	std::unique_ptr<PG::ISceneController> mainMenu(new MainMenuScene);
	m_View->replaceScene(mainMenu);
}

//--------------------------------------------------------
bool PGTestAppController::receiveTag(const int tag)
{
	switch (tag)
	{
		case TagConstants::kPopScene:
		{
			m_View->popScene();
			return true;
		}
		case TagConstants::kShowButtonsTest:
		{
			std::unique_ptr<PG::ISceneController> buttonTest(new ButtonTestScene);
			m_View->pushScene(buttonTest);
			return true;
		}
		case TagConstants::kShowAnimationsTest:
		{
			std::unique_ptr<PG::ISceneController> animationsTest(new AnimationsTestScene);
			m_View->pushScene(animationsTest);
			return true;
		}
		case TagConstants::kShowPhysicsTest:
		{
			std::unique_ptr<PG::ISceneController> physicsTest(new PhysicsTestScene);
			m_View->pushScene(physicsTest);
			return true;
		}
		case TagConstants::kShowInventoryTest:
		{
			std::unique_ptr<PG::ISceneController> inventoryTest(new InventoryTestScene);
			m_View->pushScene(inventoryTest);
			return true;
		}
		case TagConstants::kShowBarTest:
		{
			std::unique_ptr<PG::ISceneController> barTest(new BarTestScene);
			m_View->pushScene(barTest);
			return true;
		}
		case TagConstants::kShowSoundTest:
		{
			std::unique_ptr<PG::ISceneController> barTest(new SoundTestScene);
			m_View->pushScene(barTest);
			return true;
		}
		case TagConstants::kShowCameraTest:
		{
			std::unique_ptr<PG::ISceneController> barTest(new CameraTestScene);
			m_View->pushScene(barTest);
			return true;
		}
		case TagConstants::kExitApp:
		{
			m_AppHostServices->getPlatformServices().exitApp();
			return true;
		}
		default:
			return false;
	}
}

//--------------------------------------------------------
void PGTestAppController::updateFinished()
{
}
