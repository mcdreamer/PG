#pragma once

#include "PG/graphics/Node.h"
#include "PG/menu/MenuManager.h"

namespace PG {

class IScene;

//--------------------------------------------------------
class MenuLayer
{
public:
    MenuLayer(MenuManager& menuManager, IScene& scene);
    
    INode*          getLayer() const { return m_Layer.get(); }
    
private:
    NodePtr         m_Layer;
    MenuManager&    m_MenuManager;
};

}
