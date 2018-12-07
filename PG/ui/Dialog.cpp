#include "PG/ui/Dialog.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIMessage.h"
#include "PG/ui/UIPositionCalculator.h"
#include "PG/ui/Button.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
void Dialog::initUIElement(const Size& parentSize, const StyleSheet& styleSheet)
{
	UIPositionCalculator dialogCalc(styleSheet.dialogSize);
	
    auto dialogRoot = NodeCreator::createColourNode(styleSheet.dialogBackgroundColour, styleSheet.dialogSize);
    m_Root.node->setPosition(UIPositionCalculator(parentSize).atCentre());
	auto root = m_Root.node->addChild(dialogRoot);

	auto messageNode = NodeCreator::createTextNode(styleSheet.uiFontName, styleSheet.dialogFontSize);
	messageNode->setText(m_Message);
	messageNode->setPosition(Point(0, -50));
	messageNode->setColour(styleSheet.dialogTextColour);
	root.node->addChild(messageNode);
	
	int n = 0;
	for (const auto& item : m_Items)
	{
		addChild(new Button(this, Point(0, n * 50), item.getText(), item.getTag()),
				 parentSize,
				 styleSheet);
		n++;
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
