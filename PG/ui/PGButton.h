#pragma once

#include "PG/ui/PGUIElement.h"
#include "PG/graphics/Node.h"
#include "PG/core/Point.h"

#include <string>

namespace PG {

//--------------------------------------------------------
class PGButton : public PGUIElement
{
public:
    PGButton(PGTagReciever& target, const PGPoint& point, const std::string& label, int tag,
             const PGSize& forcedSize=PGSize());

    virtual void initUIElement(const StyleSheet& styleSheet) override;
    virtual void clicked(PGUIMessageQueuePoster& msgPoster) override;
 
	virtual void receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster) override {}
	
private:
    PGTagReciever&	m_Target;
    PGPoint         m_Point;
    PGSize          m_ForcedSize;
    std::string     m_Label;
    int             m_Tag;
};

}
