#pragma once

namespace PG {

class PGUIMessageQueuePoster;

//--------------------------------------------------------
class PGTagReciever
{
public:
	virtual ~PGTagReciever() {}
	
	virtual void receiveTag(const int tag, PGUIMessageQueuePoster& msgPoster)=0;
};

}
