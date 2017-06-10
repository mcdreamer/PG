#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessage.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
PGButton::PGButton(PGUIElement& target, const PGPoint& point, const std::string& label, int tag,
                   const PGSize& forcedSize)
: m_Target(target), m_Point(point), m_Label(label), m_Tag(tag), m_ForcedSize(forcedSize)
{}

//--------------------------------------------------------
void PGButton::init()
{
    auto text = NodeCreator::createTextNode("OpenSans-Regular", 40);
    text->setText(m_Label);
	auto textSize = text->getSize();
    textSize.width += 4;
    textSize.height += 4;
    
    auto bg = NodeCreator::createColourNode(255, 255, 0, 1, textSize);
    
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
