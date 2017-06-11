#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessage.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/app/StyleSheet.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
PGButton::PGButton(PGUIElement& target, const PGPoint& point, const std::string& label, int tag,
                   const PGSize& forcedSize)
: m_Target(target), m_Point(point), m_Label(label), m_Tag(tag), m_ForcedSize(forcedSize)
{}

//--------------------------------------------------------
void PGButton::init(const StyleSheet& styleSheet)
{
    auto text = NodeCreator::createTextNode(styleSheet.uiFontName, 40);
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
void PGButton::clicked(PGUIMessageQueuePoster& msgPoster)
{
    msgPoster.postMessage(PGUIMessage::sendTag(&m_Target, m_Tag));
}

}
