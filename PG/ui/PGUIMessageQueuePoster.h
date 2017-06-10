#pragma once

#include "PG/ui/PGUIMessage.h"

namespace PG {

struct PGUIMessage;

//--------------------------------------------------------
class PGUIMessageQueuePoster
{
public:
    PGUIMessageQueuePoster(PGUIMessageQueue& queue)
    : m_Queue(queue)
    {}
    
    void postMessage(const PGUIMessage& msg);
    
private:
    PGUIMessageQueue& m_Queue;
};

}
