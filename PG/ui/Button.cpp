#include "PG/ui/Button.h"
#include "PG/ui/UIMessage.h"
#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
Button::Button(const Point& point,
			   const std::string& label,
			   int tag,
			   const Size& forcedSize)
: m_Point(point),
m_ForcedSize(forcedSize),
m_Label(label),
m_Tag(tag)
{}

//--------------------------------------------------------
void Button::initUIElement(const StyleSheet& styleSheet)
{
    auto text = NodeCreator::createTextNode(styleSheet.uiFontName, styleSheet.buttonFontSize);
    text->setText(m_Label);
	text->setColour(styleSheet.buttonTextColour);
	auto textSize = text->getSize();
    textSize.width += styleSheet.buttonPadding * 2;
    textSize.height += styleSheet.buttonPadding * 2;
    
    auto bg = NodeCreator::createColourNode(styleSheet.buttonBackgroundColour, textSize);
    
    m_Root.node->setPosition(m_Point);
    m_Root.node->addChild(bg);
    m_Root.node->addChild(text);
}

//--------------------------------------------------------
void Button::clicked(UIMessageQueuePoster& msgPoster)
{
    msgPoster.postMessage(UIMessage::sendTag(nullptr, m_Tag));
}

}
