#pragma once

namespace PG {

class UIMessageQueuePoster;

//--------------------------------------------------------
class TagReciever
{
public:
	virtual ~TagReciever() {}
	
	virtual void receiveTag(const int tag, UIMessageQueuePoster& msgPoster)=0;
};

}
