#include "SoundTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/app/AppHostServices.h"
#include "PG/sound/Sound.h"
#include "PG/sound/SoundID.h"
#include "PG/sound/ISoundController.h"
#include "PG/entities/TilePositionCalculator.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kPlaySound
	};
}

//--------------------------------------------------------
struct SoundTestScene::GameState
{
	PG::SoundID soundID;
};

//--------------------------------------------------------
SoundTestScene::SoundTestScene(PG::TagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget),
m_GameState(new GameState),
m_AppHostServices(nullptr)
{}

//--------------------------------------------------------
SoundTestScene::~SoundTestScene()
{
}

//--------------------------------------------------------
void SoundTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	m_AppHostServices = &appHostServices;
	
	PG::Sound sound("buttonpress");
	
	m_GameState->soundID = m_AppHostServices->getSoundController().registerSound(sound);
	
	m_Scene.scene->setBackgroundColour(PG::Colour(100, 150, 10));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.40, 2, sceneSize.height * 0.1);
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[0], "Sound", ButtonTags::kPlaySound));
	m_Scene.scene->pushUIElement(new PG::Button(*this, btnPts[1], "Back", TagConstants::kPopScene));
}

//--------------------------------------------------------
void SoundTestScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case kPlaySound:
			m_AppHostServices->getSoundController().playSound(m_GameState->soundID);
			break;
			
		default:
			msgPoster.postMessage(PG::UIMessage::sendTag(&m_AppTagTarget, tag));
	}
}

//--------------------------------------------------------
void SoundTestScene::update(double dt)
{
}
