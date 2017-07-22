#include "MainMenuScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/app/StyleSheet.h"

//--------------------------------------------------------
void MainMenuScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(5, 0, 161));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
	logoNode->setPosition(PG::PGPoint(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
	m_Scene.scene->addChild(logoNode);

	auto textNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 120);
	textNode->setText("Test App");
	textNode->setColour(PG::Colour(255, 255, 255));
	textNode->setPosition(PG::PGPoint(sceneSize.width / 2.0, 45 + (textNode->getSize().height / 2.0)));
	m_Scene.scene->addChild(textNode);
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.4, 6, sceneSize.height * 0.1);
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[0], "Buttons Test", TagConstants::kShowButtonsTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[1], "Animations Test", TagConstants::kShowAnimationsTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[2], "Physics Test", TagConstants::kShowPhysicsTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[3], "Inventory Test", TagConstants::kShowInventoryTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[4], "Bar Test", TagConstants::kShowBarTest));
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[5], "Exit", TagConstants::kExitApp));
}

//--------------------------------------------------------
void MainMenuScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, tag));
}
