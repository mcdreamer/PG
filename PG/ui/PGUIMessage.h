#pragma once

#include <queue>

namespace PG {

class PGUIElement;

//--------------------------------------------------------
struct PGUIMessage
{
    enum Type { kClose, kSendTag, kPushElement };
    
    Type          type;
    PGUIElement*  target;
    int           tag;
    
    static PGUIMessage close(PGUIElement* target_) { return PGUIMessage { kClose, target_, 0 }; }
    static PGUIMessage sendTag(PGUIElement* target_, int tag_) { return PGUIMessage { kSendTag, target_, tag_ }; }
    static PGUIMessage pushElement(PGUIElement* target_) { return PGUIMessage { kPushElement, target_, 0 }; }
};

using PGUIMessageQueue = std::queue<PGUIMessage>;

}
