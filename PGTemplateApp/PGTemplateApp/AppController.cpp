#include "AppController.h"
#include "MainMenuScene.h"

#include "PG/app/AppConfiguration.h"
#include "PG/app/IPlatformServices.h"
#include "PG/app/AppHostServices.h"
#include "PG/graphics/View.h"

//--------------------------------------------------------
AppController::AppController()
: m_AppHostServices(nullptr),
m_View(nullptr)
{
	initialiseConfig();
}

//--------------------------------------------------------
AppController::~AppController()
{}

//--------------------------------------------------------
void AppController::initialiseConfig()
{
	m_AppConfig.windowTitle = "App";
	m_AppConfig.windowSize = PG::Size(800, 600);
	
	m_AppConfig.tileSize = 32;
	
	m_AppConfig.styleSheet.uiFontName = "OpenSans-Regular";
	m_AppConfig.styleSheet.buttonBackgroundColour = PG::Colour(150, 150, 200);
	m_AppConfig.styleSheet.buttonTextColour = PG::Colour::white();
	m_AppConfig.styleSheet.buttonPadding = 8;
}

//--------------------------------------------------------
PG::AppConfiguration AppController::getConfiguration()
{
	return m_AppConfig;
}

//--------------------------------------------------------
void AppController::start(PG::AppHostServices& appHostServices, PG::IView& view)
{
    m_AppHostServices = &appHostServices;
    m_View = &view;
	
	std::unique_ptr<PG::ISceneController> mainMenu(new MainMenuScene);
	m_View->replaceScene(mainMenu);
}

//--------------------------------------------------------
void AppController::updateFinished()
{
}
