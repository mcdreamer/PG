#include "ButtonsTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/app/StyleSheet.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kTagTestButton = 0,
		kTagAnotherTestButton
	};
}

//--------------------------------------------------------
void ButtonTestScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(0, 0, 0));
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 100), "Back", TagConstants::kPopScene));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 200), "Test Button", kTagTestButton));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(200, 300), "Another Test Button", kTagAnotherTestButton));
	
	auto textNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 30);
	textNode->setText("Hello");
	textNode->setColour(PG::Colour(0, 255, 255));
	textNode->setPosition(PG::PGPoint(200, 400));
	m_Text = m_Scene.scene->addChild(textNode);
}

//--------------------------------------------------------
void ButtonTestScene::keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods)
{
	if (code == PG::PGKeyCode::PGKeyCodeUp)
	{
		m_Text.node->setPosition(PG::PGPoint(m_Text.node->getPosition().x, m_Text.node->getPosition().y - 1));
	}
	else if (code == PG::PGKeyCode::PGKeyCodeDown)
	{
		m_Text.node->setPosition(PG::PGPoint(m_Text.node->getPosition().x, m_Text.node->getPosition().y + 1));
	}
}

//--------------------------------------------------------
void ButtonTestScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case kTagTestButton:
			m_Text.node->setText("Clicked!");
			break;
			
		case kTagAnotherTestButton:
			m_Text.node->setText("Another Clicked!");
			break;

		default:
			msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, TagConstants::kPopScene));
			break;
	}
}
