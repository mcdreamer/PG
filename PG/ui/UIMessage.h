#pragma once

#include <queue>

namespace PG {

class UIElement;
class TagReciever;

//--------------------------------------------------------
struct UIMessage
{
    enum Type { kClose, kSendTag, kPushElement };
    
    Type			type;
    TagReciever*  target;
    int				tag;
    
    static UIMessage close(UIElement* target_);
    static UIMessage sendTag(TagReciever* target_, int tag_);
    static UIMessage pushElement(UIElement* target_);
};

using PGUIMessageQueue = std::queue<UIMessage>;

}
