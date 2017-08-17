#pragma once

#include "PG/console/CommandSetHandle.h"

namespace PG {

class ConsoleController;

//! Automatically removes a console command set on destruction
//--------------------------------------------------------
class CommandSetRemover
{
public:
	CommandSetRemover(ConsoleController& consoleController,
					  const CommandSetHandle& handle)
	: m_ConsoleController(consoleController),
	m_Handle(handle)
	{}
	
	~CommandSetRemover();
	
private:
	ConsoleController&	m_ConsoleController;
	CommandSetHandle	m_Handle;
};
	
}
