#pragma once

namespace PG {

//--------------------------------------------------------
class CommandSetHandle
{
public:
	explicit CommandSetHandle(int setID)
	: m_SetID(setID)
	{}
	
	bool operator==(const CommandSetHandle& other) const;
	
private:
	int	m_SetID;
};

}
