#pragma once

#include <queue>

namespace PG {

class UIElement;
class TagReceiver;

//--------------------------------------------------------
struct UIMessage
{
    enum Type { kClose, kSendTag };
    
    Type			type;
    TagReceiver*	target;
    int				tag;
    
    static UIMessage close(UIElement* target_);
    static UIMessage sendTag(TagReceiver* target_, int tag_);
	static UIMessage sendTag(int tag_);
};

using PGUIMessageQueue = std::queue<UIMessage>;

}
