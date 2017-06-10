#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/ui/PGUIMessage.h"

namespace PG {

//--------------------------------------------------------
void PGUIMessageQueuePoster::postMessage(const PGUIMessage& msg)
{
    m_Queue.push(msg);
}

}
