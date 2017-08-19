#include "MainMenuScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
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
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.35, 7, sceneSize.height * 0.1);
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[0], "Buttons Test", TagConstants::kShowButtonsTest));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[1], "Animations Test", TagConstants::kShowAnimationsTest));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[2], "Physics Test", TagConstants::kShowPhysicsTest));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[3], "Inventory Test", TagConstants::kShowInventoryTest));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[4], "Bar Test", TagConstants::kShowBarTest));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[5], "Sound Test", TagConstants::kShowSoundTest));
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[6], "Exit", TagConstants::kExitApp));
}

//--------------------------------------------------------
void MainMenuScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::UIMessage::sendTag(&m_AppTagTarget, tag));
}
