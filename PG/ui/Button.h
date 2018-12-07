#pragma once

#include "PG/ui/UIElement.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <string>

namespace PG {

class TagReceiver;
	
//--------------------------------------------------------
class Button : public UIElement
{
public:
    Button(const Point& point,
		   const std::string& label,
		   int tag,
           const Size& forcedSize=Size());
	
	Button(TagReceiver* parent,
		   const Point& point,
		   const std::string& label,
		   int tag,
		   const Size& forcedSize=Size());

private:
    virtual void initUIElement(const Size& parentSize, const StyleSheet& styleSheet) override;
    virtual void clicked(UIMessageQueuePoster& msgPoster) override;
	
	TagReceiver*	m_Parent;
    Point			m_Point;
    Size			m_ForcedSize;
    std::string     m_Label;
    int             m_Tag;
};

}
