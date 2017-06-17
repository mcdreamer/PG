#include "PG/ui/PGDialog.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
void PGDialog::initUIElement(const StyleSheet& styleSheet)
{
    auto dialogRoot = NodeCreator::createSpriteNode("dialog");
    m_Root.node->setPosition(PGPoint(284, 160));
    auto dialogRootHandle = m_Root.node->addChild(dialogRoot);
    
    setupDialog(dialogRootHandle);
}

}
