#include "AnimationsTestScene.h"
#include "TagConstants.h"

#include "PG/animation/MoveToAnimation.h"
#include "PG/animation/TextureAnimationUtils.h"
#include "PG/animation/TextureAnimationDefinition.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/ui/UI.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/GameConstants.h"

//--------------------------------------------------------
void AnimationsTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(161, 5, 5));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
	logoNode->setPosition(PG::Point(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
	auto logoHandle = m_Scene.scene->addChild(logoNode);
	PG::AnimationPtr moveTo(new PG::MoveToAnimation(logoHandle, PG::Point(500, 400), 5));
	m_Scene.scene->addAnimation(moveTo);
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	
	PG::TextureAnimationUtils::createAndAddAnimatedTexture(PG::TextureAnimationDefinition(1.0 / 14.0, 10, PG::Size(32.0, 32.0)),
														   "bouncingball",
														   uiPosCalc.fromTopMid(PG::Size(0, 32)),
														   m_Scene);

	PG::TextureAnimationUtils::createAndAddAnimatedTexture(PG::TextureAnimationDefinition(1.0 / 14.0, 10, PG::Size(32.0, 32.0)),
														   "bouncingball2",
														   uiPosCalc.fromTopMid(PG::Size(50, 32)),
														   m_Scene);
	
	auto& ui = m_Scene.scene->getUILayer();
	ui.pushElement(new PG::Button(uiPosCalc.fromBottomMid(PG::Size(0, sceneSize.height * 0.25)), "Back", TagConstants::kPopScene));
}

//--------------------------------------------------------
void AnimationsTestScene::update(double dt)
{

}
