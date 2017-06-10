#pragma once

#include "PG/ui/PGUIMessage.h"
#include "PG/ui/PGUIElement.h"

namespace PG {

class IScene;

//--------------------------------------------------------
class PGUI
{
public:
    PGUI(IScene& scene)
    : m_Scene(scene)
    {}
    
    void pushElement(PGUIElement* element);
    bool handleClick(const PGPoint& screenPt);
    void update();
  
private:
    PGUIMessageQueue    m_MessageQueue;
    PGUIElementArray    m_UIStack;
    IScene&             m_Scene;
};

}
