#pragma once

#include <functional>
#include <string>
#include <vector>
#include <map>

#include <boost/optional.hpp>

namespace PG {

class RawConsoleCommand;
class ConsoleCommandArgument;
enum class ConsoleCommandArgumentType;

using ConsoleCommandHandlerFunc = std::function<std::string (const std::vector<ConsoleCommandArgument>&)>;

//--------------------------------------------------------
class ConsoleCommandRegistry
{
	//--------------------------------------------------------
	struct CommandInfo
	{
		ConsoleCommandHandlerFunc				handler;
		std::vector<ConsoleCommandArgumentType>	argumentTypes;
	};

public:
	ConsoleCommandRegistry();

	void		addHandler(const std::string& commandName,
						   const ConsoleCommandHandlerFunc& handlerFunc,
						   const std::vector<ConsoleCommandArgumentType>& argumentTypes);
	
	boost::optional<std::string> handleCommand(const RawConsoleCommand& command);

	void		setNArgumentsString(const std::string& str) { m_NArgumentsString = str; }
	void		setErrorString(const std::string& str) { m_ErrorString = str; }

private:
	std::map<std::string, CommandInfo>	m_Handlers;
	std::string							m_NArgumentsString;
	std::string							m_ErrorString;
};
	
}
