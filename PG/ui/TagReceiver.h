#pragma once

namespace PG {
	
class UIMessageQueuePoster;

//--------------------------------------------------------
class TagReceiver
{
public:
	virtual ~TagReceiver() {}
	
	virtual bool receiveTag(const int tag, UIMessageQueuePoster& msgPoster) { return false; }
};

}
