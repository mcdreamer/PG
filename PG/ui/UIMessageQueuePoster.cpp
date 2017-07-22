#include "PG/ui/UIMessageQueuePoster.h"
#include "PG/ui/UIMessage.h"

namespace PG {

//--------------------------------------------------------
void UIMessageQueuePoster::postMessage(const UIMessage& msg)
{
    m_Queue.push(msg);
}

}
