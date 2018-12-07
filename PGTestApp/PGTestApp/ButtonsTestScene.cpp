#include "ButtonsTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/ui/Button.h"
#include "PG/ui/Dialog.h"
#include "PG/ui/UI.h"
#include "PG/app/StyleSheet.h"
#include "PG/app/AppHostServices.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kTagTestButton = 0,
		kTagAnotherTestButton,
		kTagShowDialog
	};
}

//--------------------------------------------------------
void ButtonTestScene::initScene(PG::AppHostServices& appHostServices, PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(0, 0, 0));
	
	auto& ui = m_Scene.scene->getUILayer();
	ui.pushElement(new PG::Button(PG::Point(200, 100), "Back", TagConstants::kPopScene));
	ui.pushElement(new PG::Button(PG::Point(200, 200), "Test Button", kTagTestButton));
	ui.pushElement(new PG::Button(PG::Point(200, 300), "Another Test Button", kTagAnotherTestButton));
	ui.pushElement(new PG::Button(PG::Point(200, 400), "Dialog", kTagShowDialog));
	
	auto textNode = PG::NodeCreator::createTextNode(appHostServices.getStyleSheet().uiFontName, 30);
	textNode->setText("Hello");
	textNode->setColour(PG::Colour(0, 255, 255));
	textNode->setPosition(PG::Point(200, 500));
	m_Text = m_Scene.scene->addChild(textNode);
}

//--------------------------------------------------------
bool ButtonTestScene::receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case kTagTestButton:
			m_Text.node->setText("Clicked!");
			return true;
			
		case kTagAnotherTestButton:
			m_Text.node->setText("Another Clicked!");
			return true;
			
		case kTagShowDialog:
			m_Text.node->setText("Dialog");
			m_Scene.scene->getUILayer().pushElement(new PG::Dialog("This is a dialog",
																   { PG::Dialog::Item("Yes", 101), PG::Dialog::Item("No", 102) },
																   [this](int ret) { m_Text.node->setText(std::to_string(ret)); }));
			return true;

		default:
			return false;
	}
}
