#pragma once

#include "PG/ui/PGTagReceiver.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <vector>

namespace PG {

class IScene;
class PGRect;
struct StyleSheet;

class PGUIMessageQueuePoster;
class PGUIElement;
using PGUIElementArray = std::vector<std::unique_ptr<PGUIElement>>;

//--------------------------------------------------------
class PGUIElement : public PGTagReciever
{
public:
    virtual ~PGUIElement() {}
    
    void                show(IScene& scene, const StyleSheet& styleSheet);
    void                show(NodeHandle parent, const StyleSheet& styleSheet);
    void                close();
    
    void                addChild(PGUIElement* element, const StyleSheet& styleSheet);
    void                addChild(std::unique_ptr<PGUIElement>& element, const StyleSheet& styleSheet);
    
    bool                handleClick(const PGPoint& parentRelPt, PGUIMessageQueuePoster& msgPoster);
    
    virtual PGRect      getElementRect() const;
    
    virtual void        initUIElement(const StyleSheet& styleSheet)=0;
    virtual void        clicked(PGUIMessageQueuePoster& msgPoster) {}
	
protected:
    NodeHandle          m_Root;
    
private:
    PGUIElementArray    m_Children;
};

}
