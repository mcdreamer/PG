#include "SoundTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
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
	PG::SoundID buttonSoundID;
	PG::SoundID cymbalSoundID;
	
	bool		playCymbal = false;
};

//--------------------------------------------------------
SoundTestScene::SoundTestScene()
: m_AppHostServices(nullptr),
m_GameState(new GameState)
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
	
	PG::Sound buttonPress("buttonpress");
	buttonPress.pitchRange = PG::ValueRange<float>(0.9f, 1.1f);
	buttonPress.volumeRange = PG::ValueRange<float>(80.0f, 100.f);
	m_GameState->buttonSoundID = m_AppHostServices->getSoundController().registerSound(buttonPress);
	
	PG::Sound cymbal("cymbal");
	cymbal.pitchRange = PG::ValueRange<float>(0.9f, 1.1f);
	cymbal.volumeRange = PG::ValueRange<float>(80.0f, 100.f);
	m_GameState->cymbalSoundID = m_AppHostServices->getSoundController().registerSound(cymbal);
	
	m_Scene.scene->setBackgroundColour(PG::Colour(100, 150, 10));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.40, 2, sceneSize.height * 0.1);
	
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[0], "Sound", ButtonTags::kPlaySound));
	m_Scene.scene->pushUIElement(new PG::Button(btnPts[1], "Back", TagConstants::kPopScene));
}

//--------------------------------------------------------
bool SoundTestScene::receiveTag(const int tag)
{
	switch (tag)
	{
		case kPlaySound:
			m_AppHostServices->getSoundController().playSound(m_GameState->playCymbal ? m_GameState->cymbalSoundID : m_GameState->buttonSoundID);
			m_GameState->playCymbal = !m_GameState->playCymbal;
			return true;
			
		default:
			return false;
	}
}
