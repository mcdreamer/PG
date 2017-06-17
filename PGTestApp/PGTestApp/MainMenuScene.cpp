#include "MainMenuScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
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
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.50), "Buttons Test", TagConstants::kShowButtonsTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.70), "Animations Test", TagConstants::kShowAnimationsTest));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.90), "Exit", TagConstants::kExitApp));
}

//--------------------------------------------------------
void MainMenuScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, tag));
}
