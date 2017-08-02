#pragma once

#include <string>

namespace PG {

//--------------------------------------------------------
class ConsoleCommandArgument
{
public:
	ConsoleCommandArgument(const std::string& val)
	: str(val)
	{}
	
	ConsoleCommandArgument(const int& val)
	: num(val)
	{}
	
	const std::string&	getValueAsString() const { return str; }
	const int&			getValueAsInt() const { return num; }
	
private:
	std::string	str;
	int			num;
};

}
