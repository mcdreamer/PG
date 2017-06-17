#pragma once

#include <queue>

namespace PG {

class PGUIElement;
class PGTagReciever;

//--------------------------------------------------------
struct PGUIMessage
{
    enum Type { kClose, kSendTag, kPushElement };
    
    Type			type;
    PGTagReciever*  target;
    int				tag;
    
    static PGUIMessage close(PGUIElement* target_);
    static PGUIMessage sendTag(PGTagReciever* target_, int tag_);
    static PGUIMessage pushElement(PGUIElement* target_);
};

using PGUIMessageQueue = std::queue<PGUIMessage>;

}
