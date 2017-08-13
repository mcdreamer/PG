#include "AnimationsTestScene.h"
#include "TagConstants.h"

#include "PG/animation/AnimationUpdater.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/app/StyleSheet.h"

//--------------------------------------------------------
void AnimationsTestScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(161, 5, 5));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	auto logoNode = PG::NodeCreator::createSpriteNode("PGlogo");
	logoNode->setPosition(PG::Point(30 + (logoNode->getSize().width / 2.0), 30 + (logoNode->getSize().height / 2.0)));
	auto logoHandle = m_Scene.scene->addChild(logoNode);
	m_Animations.emplace_back(new PG::MoveToAnimation(logoHandle, PG::Point(500, 400), 5));
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, uiPosCalc.fromBottomMid(PG::Size(0, sceneSize.height * 0.25)), "Back", TagConstants::kPopScene));
}

//--------------------------------------------------------
void AnimationsTestScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	msgPoster.postMessage(PG::UIMessage::sendTag(&m_AppTagTarget, tag));
}

//--------------------------------------------------------
void AnimationsTestScene::update(double dt)
{
	PG::AnimationUpdater animUpdater;
	
	animUpdater.updateAnimations(m_Animations, dt);
	
	animUpdater.removeCompletedAnimations(m_Animations);
}
