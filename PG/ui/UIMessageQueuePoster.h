#pragma once

#include "PG/ui/UIMessage.h"

namespace PG {

struct UIMessage;

//--------------------------------------------------------
class UIMessageQueuePoster
{
public:
    UIMessageQueuePoster(PGUIMessageQueue& queue)
    : m_Queue(queue)
    {}
    
    void postMessage(const UIMessage& msg);
    
private:
    PGUIMessageQueue& m_Queue;
};

}
