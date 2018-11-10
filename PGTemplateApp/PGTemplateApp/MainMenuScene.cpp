#include "MainMenuScene.h"

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
	
	m_Scene.scene->setBackgroundColour(PG::Colour(44, 62, 80));

	const auto sceneSize = m_Scene.scene->getSceneSize();
	PG::UIPositionCalculator uiPosCalc(sceneSize);

	auto textNode = PG::NodeCreator::createTextNode(appHostServices.getStyleSheet().uiFontName, 120);
	textNode->setText("Hello");
	textNode->setColour(PG::Colour(46, 204, 113));
	textNode->setPosition(uiPosCalc.atCentre());
	m_Scene.scene->addChild(textNode);
}
