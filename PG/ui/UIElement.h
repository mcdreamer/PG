#pragma once

#include "PG/ui/TagReceiver.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <vector>

namespace PG {

class IScene;
class Rect;
struct StyleSheet;

class UIMessageQueuePoster;
class UIElement;
using UIElementArray = std::vector<std::unique_ptr<UIElement>>;

//--------------------------------------------------------
class UIElement : public TagReciever
{
public:
    virtual ~UIElement() {}
    
//    void                show(IScene& scene, const StyleSheet& styleSheet);
    void                show(NodeHandle parent, const StyleSheet& styleSheet);
    void                close();
    
    void                addChild(UIElement* element, const StyleSheet& styleSheet);
    void                addChild(std::unique_ptr<UIElement>& element, const StyleSheet& styleSheet);
    
    bool                handleClick(const Point& parentRelPt, UIMessageQueuePoster& msgPoster);
    
    virtual Rect      getElementRect() const;
    
    virtual void        initUIElement(const StyleSheet& styleSheet)=0;
    virtual void        clicked(UIMessageQueuePoster& msgPoster) {}
	
protected:
    NodeHandle          m_Root;
    
private:
    UIElementArray    m_Children;
};

}
