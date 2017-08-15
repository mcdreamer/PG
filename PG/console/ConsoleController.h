#pragma once

#include "PG/console/ConsoleCommandRegistry.h"
#include "PG/console/RawConsoleCommand.h"
#include "PG/console/CommandSetHandle.h"
#include "PG/core/BindableValue.h"

#include <vector>
#include <string>

namespace PG {

enum class KeyCode;

//--------------------------------------------------------
class ConsoleController
{
public:
	ConsoleController();
	
	void							setCommandNotFoundString(const std::string& notFoundString);
	CommandSetHandle				addCommandSet(const ConsoleCommandRegistry& registry);
	void							removeCommandSet(const CommandSetHandle& setHandle);

	void							keyPressed(const KeyCode& code);
	
	PG::BindableValue<std::string>&	getConsoleInput() { return m_ConsoleInput; }
	PG::BindableValue<int>&			getConsoleOutputSize() { return m_ConsoleOutputSize; }
	const std::vector<std::string>&	getConsoleOutput() const { return m_ConsoleOutput; }
	
private:
	std::vector<std::pair<CommandSetHandle, ConsoleCommandRegistry>>	m_CommandSets;
	int																	m_NextSetID;
	std::string															m_NotFoundString;
	
	PG::BindableValue<std::string>										m_ConsoleInput;
	PG::BindableValue<int>												m_ConsoleOutputSize;
	std::vector<std::string>											m_ConsoleOutput;

	void		addCaret();
	void		removeCaret();
	std::string handleInputAndGetOutput(const std::string& input);
};

}
