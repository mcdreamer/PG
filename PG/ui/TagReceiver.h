#pragma once

namespace PG {

//--------------------------------------------------------
class TagReceiver
{
public:
	virtual ~TagReceiver() {}
	
	virtual bool receiveTag(const int tag) { return false; }
};

}
