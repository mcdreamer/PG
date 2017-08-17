#include "PG/console/CommandSetRemover.h"
#include "PG/console/ConsoleController.h"

namespace PG {

//--------------------------------------------------------
CommandSetRemover::~CommandSetRemover()
{
	m_ConsoleController.removeCommandSet(m_Handle);
}

}
