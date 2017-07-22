#pragma once

#include "PG/ui/UIElement.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <string>

namespace PG {

//--------------------------------------------------------
class Button : public UIElement
{
public:
    Button(TagReciever& target, const Point& point, const std::string& label, int tag,
           const Size& forcedSize=Size());

    virtual void initUIElement(const StyleSheet& styleSheet) override;
    virtual void clicked(UIMessageQueuePoster& msgPoster) override;
 
	virtual void receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override {}
	
private:
    TagReciever&	m_Target;
    Point         m_Point;
    Size          m_ForcedSize;
    std::string     m_Label;
    int             m_Tag;
};

}
