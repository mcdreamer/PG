#include "PG/console/CommandSetHandle.h"

namespace PG {

//--------------------------------------------------------
bool CommandSetHandle::operator==(const CommandSetHandle& other) const
{
	return m_SetID == other.m_SetID;
}

}
