#pragma once

#include "PG/graphics/NodeCreator.h"
#include "PG/core/Point.h"

#include <vector>

namespace PG {

class IScene;
class PGRect;

class PGUIMessageQueuePoster;
class PGUIElement;
using PGUIElementArray = std::vector<std::unique_ptr<PGUIElement>>;

//--------------------------------------------------------
class PGUIElement
{
public:
    virtual ~PGUIElement() {}
    
    void                show(IScene& scene);
    void                show(NodeHandle parent);
    void                close();
    
    void                addChild(PGUIElement* element);
    void                addChild(std::unique_ptr<PGUIElement>& element);
    
    bool                handleClick(const PGPoint& parentRelPt, PGUIMessageQueuePoster& msgPoster);
    
    virtual PGRect      getElementRect() const;
    
    virtual void        init()=0;
    virtual void        clicked(PGUIMessageQueuePoster& msgPoster) {}
    virtual void        receiveTag(const int tag, PGUIMessageQueuePoster& msgPoster) {}
    
protected:
    NodeHandle          m_Root;
    
private:
    PGUIElementArray    m_Children;
};

}
