#include "PG/console/ConsoleCommandRegistry.h"
#include "PG/console/ConsoleCommandArgument.h"
#include "PG/console/ConsoleCommandArgumentType.h"
#include "PG/console/RawConsoleCommand.h"

#include <boost/lexical_cast.hpp>

namespace PG {

//--------------------------------------------------------
ConsoleCommandRegistry::ConsoleCommandRegistry()
: m_NotFoundString("Command not found"),
m_NArgumentsString("Incorrect argument count. Requires"),
m_ErrorString("Error")
{}

//--------------------------------------------------------
void ConsoleCommandRegistry::addHandler(const std::string& commandName,
										const ConsoleCommandHandlerFunc& handlerFunc,
										const std::vector<ConsoleCommandArgumentType>& argumentTypes)
{
	m_Handlers[commandName] = CommandInfo { handlerFunc, argumentTypes };
}

namespace
{
	//--------------------------------------------------------
	bool parseArguments(const std::vector<std::string>& rawArguments,
						const std::vector<ConsoleCommandArgumentType>& argumentTypes,
						std::vector<ConsoleCommandArgument>& parsedArgs)
	{
		try
		{
			auto argTypeIt = argumentTypes.begin();
			for (const auto& rawArgument : rawArguments)
			{
				switch (*argTypeIt)
				{
					case ConsoleCommandArgumentType::kInt:
						parsedArgs.emplace_back(std::move(boost::lexical_cast<int>(rawArgument)));
						break;
					case ConsoleCommandArgumentType::kString:
						parsedArgs.emplace_back(std::move(rawArgument));
						break;
				}
				
				++argTypeIt;
			}
			
			return true;
		}
		catch (std::exception& e)
		{
			return false;
		}
	}
}

//--------------------------------------------------------
std::string ConsoleCommandRegistry::handleCommand(const RawConsoleCommand& command)
{
	auto handlerIt = m_Handlers.find(command.getCommandName());
	if (handlerIt != m_Handlers.end())
	{
		auto& commandInfo = handlerIt->second;
		
		if (commandInfo.argumentTypes.size() == command.getArguments().size())
		{
			std::vector<ConsoleCommandArgument> parsedArgs;
			if (parseArguments(command.getArguments(), commandInfo.argumentTypes, parsedArgs))
			{
				return commandInfo.handler(parsedArgs);
			}
			else
			{
				return m_ErrorString;
			}
		}
		else
		{
			return m_NArgumentsString + " " + std::to_string(commandInfo.argumentTypes.size());
		}
	}
	
	return m_NotFoundString;
}

}
