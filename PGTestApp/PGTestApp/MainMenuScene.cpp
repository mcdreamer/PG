#include "MainMenuScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/AppHostServices.h"

//--------------------------------------------------------
void MainMenuScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(5, 0, 161));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
	logoNode->setPosition(PG::Point(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
	m_Scene.scene->addChild(logoNode);

	auto textNode = PG::NodeCreator::createTextNode(appHostServices.getStyleSheet().uiFontName, 120);
	textNode->setText("Test App");
	textNode->setColour(PG::Colour(255, 255, 255));
	textNode->setPosition(PG::Point(sceneSize.width / 2.0, 45 + (textNode->getSize().height / 2.0)));
	m_Scene.scene->addChild(textNode);
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.32, 8, sceneSize.height * 0.09);
	
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[0], "Buttons Test", TagConstants::kShowButtonsTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[1], "Animations Test", TagConstants::kShowAnimationsTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[2], "Physics Test", TagConstants::kShowPhysicsTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[3], "Inventory Test", TagConstants::kShowInventoryTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[4], "Bar Test", TagConstants::kShowBarTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[5], "Sound Test", TagConstants::kShowSoundTest));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[6], "Camera Test", TagConstants::kShowCameraTest));
	
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[7], "Exit", TagConstants::kExitApp));
}
