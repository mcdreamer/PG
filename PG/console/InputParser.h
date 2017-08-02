#pragma once

#include <string>

#include <boost/optional.hpp>

namespace PG {

struct ConsoleCommand;

//--------------------------------------------------------
class InputParser
{
public:
	boost::optional<ConsoleCommand> parseInput(const std::string& input) const;
};

}
