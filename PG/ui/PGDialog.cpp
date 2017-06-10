#include "PG/ui/PGDialog.h"

namespace PG {

//--------------------------------------------------------
void PGDialog::init()
{
    auto dialogRoot = NodeCreator::createSpriteNode("dialog");
    m_Root.node->setPosition(PGPoint(284, 160));
    auto dialogRootHandle = m_Root.node->addChild(dialogRoot);
    
    setupDialog(dialogRootHandle);
}

}
