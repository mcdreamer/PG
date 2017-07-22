#include "PG/ui/Dialog.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
void Dialog::initUIElement(const StyleSheet& styleSheet)
{
    auto dialogRoot = NodeCreator::createSpriteNode("dialog");
    m_Root.node->setPosition(Point(284, 160));
    auto dialogRootHandle = m_Root.node->addChild(dialogRoot);
    
    setupDialog(dialogRootHandle);
}

}
