#include "ButtonsTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/AppHostServices.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kTagTestButton = 0,
		kTagAnotherTestButton
	};
}

//--------------------------------------------------------
void ButtonTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(0, 0, 0));
	
	m_Scene.scene->pushUIElement(new PG::Button(PG::Point(200, 100), "Back", TagConstants::kPopScene));
	m_Scene.scene->pushUIElement(new PG::Button(PG::Point(200, 200), "Test Button", kTagTestButton));
	m_Scene.scene->pushUIElement(new PG::Button(PG::Point(200, 300), "Another Test Button", kTagAnotherTestButton));
	
	auto textNode = PG::NodeCreator::createTextNode(appHostServices.getStyleSheet().uiFontName, 30);
	textNode->setText("Hello");
	textNode->setColour(PG::Colour(0, 255, 255));
	textNode->setPosition(PG::Point(200, 400));
	m_Text = m_Scene.scene->addChild(textNode);
}

//--------------------------------------------------------
bool ButtonTestScene::receiveTag(const int tag)
{
	switch (tag)
	{
		case kTagTestButton:
			m_Text.node->setText("Clicked!");
			return true;
			
		case kTagAnotherTestButton:
			m_Text.node->setText("Another Clicked!");
			return true;

		default:
			return false;
	}
}
