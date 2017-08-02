#pragma once

#include <string>
#include <vector>

namespace PG {

//--------------------------------------------------------
class ConsoleCommand
{
public:
	ConsoleCommand(const std::string& commandName,
				   const std::vector<std::string>& arguments)
	: m_CommandName(commandName),
	m_Arguments(arguments)
	{}
	
	const std::string&				getCommandName() const { return m_CommandName; }
	const std::vector<std::string>& getArguments() const { return m_Arguments; }
	
private:
	std::string					m_CommandName;
	std::vector<std::string>	m_Arguments;
};

}
