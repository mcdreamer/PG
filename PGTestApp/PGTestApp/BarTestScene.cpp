#include "BarTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/ui/Button.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/BindableValue.h"
#include "PG/ui/Bar.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kTagIncrease = 0,
		kTagDecrease
	};
}

//--------------------------------------------------------
struct BarTestScene::GameState
{
	GameState()
	: value(50)
	{}

	PG::BindableValue<int> value;
};

//--------------------------------------------------------
BarTestScene::BarTestScene(PG::TagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget),
m_GameState(new GameState)
{}

//--------------------------------------------------------
BarTestScene::~BarTestScene()
{
}

//--------------------------------------------------------
void BarTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(100, 10, 150));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.40, 4, sceneSize.height * 0.1);

	m_Scene.scene->pushUIElement(new PG::Bar(btnPts[0], PG::Size(50, 40),
											 PG::BarStyle::kBasic, PG::ValueRange<int>(0, 100), m_GameState->value));

	m_Scene.scene->pushUIElement(new PG::Bar(btnPts[1], PG::Size(300, 20),
											 PG::BarStyle::kBasic, PG::ValueRange<int>(0, 100), m_GameState->value));
	
	m_Scene.scene->pushUIElement(new PG::Bar(btnPts[2], PG::Size(100, 5),
											 PG::BarStyle::kBasic, PG::ValueRange<int>(0, 100), m_GameState->value));
	
	m_Scene.scene->pushUIElement(new PG::Bar(btnPts[3], PG::Size(200, 10),
											 PG::BarStyle::kBasic, PG::ValueRange<int>(0, 100), m_GameState->value));
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, PG::Point(sceneSize.width * 0.4, sceneSize.height * 0.8), "+", ButtonTags::kTagIncrease));
	m_Scene.scene->pushUIElement(new PG::Button(*this, PG::Point(sceneSize.width * 0.6, sceneSize.height * 0.8), "-", ButtonTags::kTagDecrease));
	
	m_Scene.scene->pushUIElement(new PG::Button(*this, PG::Point(sceneSize.width / 2.0, sceneSize.height * 0.95), "Back", TagConstants::kPopScene));
}

//--------------------------------------------------------
void BarTestScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case kTagIncrease:
			++m_GameState->value;
			break;
			
		case kTagDecrease:
			--m_GameState->value;
			break;
			
		default:
			msgPoster.postMessage(PG::UIMessage::sendTag(&m_AppTagTarget, tag));
	}
}

//--------------------------------------------------------
void BarTestScene::update(double dt)
{
}
