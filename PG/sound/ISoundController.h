#pragma once

namespace PG {

class SoundID;
struct Sound;

//--------------------------------------------------------
class ISoundController
{
public:
	virtual ~ISoundController() {}
	
	virtual SoundID registerSound(const Sound& sound)=0;
	virtual void	playSound(const SoundID& soundID)=0;
};

}
