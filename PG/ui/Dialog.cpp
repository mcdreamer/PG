#include "PG/ui/Dialog.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIMessage.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/ui/Button.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
NodePtr Dialog::createRoot(const Size& parentSize, const StyleSheet& styleSheet)
{
	auto dialogRoot = NodeCreator::createColourNode(styleSheet.dialogBackgroundColour, styleSheet.dialogSize);
	dialogRoot->setPosition(UIPositionCalculator(parentSize).atCentre());
	
	return dialogRoot;
}
	
//--------------------------------------------------------
void Dialog::initUIElement(const Size& parentSize, const StyleSheet& styleSheet)
{
	UIPositionCalculator dialogCalc(styleSheet.dialogSize);

	const auto titlePos = dialogCalc.fromTopMid(PG::Size(0, 40));
	auto messageNode = NodeCreator::createTextNode(styleSheet.uiFontName, styleSheet.dialogFontSize);
	messageNode->setText(m_Message);
	messageNode->setPosition(titlePos);
	messageNode->setColour(styleSheet.dialogTextColour);
	m_Root.node->addChild(messageNode);
	
	const auto buttonPositions = dialogCalc.multipleDownCentre(styleSheet.dialogSize.height / 2.0, m_Items.size(), 40);
	
	int nthButton = 0;
	for (const auto& item : m_Items)
	{
		addChild(new Button(this, buttonPositions[nthButton], item.getText(), item.getTag()),
				 parentSize,
				 styleSheet);
		nthButton++;
	}
}

//-----------------------------------------------------------------
bool Dialog::receiveTag(const int tag, UIMessageQueuePoster& msgPoster)
{
	m_Callback(tag);
	
	msgPoster.postMessage(UIMessage::close(this));
	
	return true; // swallow all tags
}

//-----------------------------------------------------------------
bool Dialog::isModal() const
{
	return true;
}
	
}
