#include "PG/menu/MenuLayer.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
MenuLayer::MenuLayer(MenuManager& menuManager, IScene& scene)
: m_MenuManager(menuManager)
{
    m_Layer = NodeCreator::createNode();
    
    m_MenuManager.initAndDisplayMenu(*m_Layer);
}

}
