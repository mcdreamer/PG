#pragma once

#include "PG/ui/TagReceiver.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <vector>

namespace PG {

class Rect;
struct StyleSheet;

class UIMessageQueuePoster;
class UIElement;
using UIElementArray = std::vector<std::unique_ptr<UIElement>>;

//--------------------------------------------------------
class UIElement : public TagReceiver
{
public:
    virtual ~UIElement() {}
    
    void                show(NodeHandle parent, const Size& parentSize, const StyleSheet& styleSheet);
    void                close();
    
    void                addChild(UIElement* element, const Size& parentSize, const StyleSheet& styleSheet);
    void                addChild(std::unique_ptr<UIElement>& element, const Size& parentSize, const StyleSheet& styleSheet);

	bool                handleClick(const Point& parentRelPt, UIMessageQueuePoster& msgPoster);
	
	virtual void        initUIElement(const Size& parentSize, const StyleSheet& styleSheet)=0;
	virtual void        clicked(UIMessageQueuePoster& msgPoster) {}
	
	virtual	bool		isModal() const { return false; }
	
protected:
    NodeHandle          m_Root;
	
	virtual NodePtr		createRoot(const Size& parentSize, const StyleSheet& styleSheet);
	
private:
    UIElementArray		m_Children;
	
	Rect				getElementRect() const;
};

}
