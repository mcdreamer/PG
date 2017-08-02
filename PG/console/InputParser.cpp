#include "PG/console/InputParser.h"
#include "PG/console/ConsoleCommand.h"

#include <boost/tokenizer.hpp>

namespace PG {

//--------------------------------------------------------
boost::optional<ConsoleCommand> InputParser::parseInput(const std::string& input) const
{
	typedef boost::tokenizer<boost::char_separator<char>> cmd_tokenizer;
	boost::char_separator<char> sep{" "};
	cmd_tokenizer tokenizer(input, sep);
	
	std::string commandName;
	std::vector<std::string> arguments;
	
	for (const auto& token : tokenizer)
	{
		if (commandName.empty())
		{
			commandName = token;
		}
		else
		{
			arguments.push_back(token);
		}
	}

	if (commandName.empty())
	{
		return boost::none;
	}
	
	return ConsoleCommand(commandName, arguments);
}

}
