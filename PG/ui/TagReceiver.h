#pragma once

namespace PG {

class UIMessageQueuePoster;

//--------------------------------------------------------
class TagReciever
{
public:
	virtual ~TagReciever() {}
	
	virtual bool receiveTag(const int tag) { return false; }
};

}
