#pragma once

#include <string>

#include <boost/optional.hpp>

namespace PG {

class RawConsoleCommand;

//--------------------------------------------------------
class InputParser
{
public:
	boost::optional<RawConsoleCommand> parseInput(const std::string& input) const;
};

}
