#pragma once

namespace PG {

//--------------------------------------------------------
class SoundID
{
public:
	explicit SoundID(int soundID)
	: m_SoundID(soundID)
	{}
	
	bool operator==(const SoundID& other) const;
	bool operator<(const SoundID& other) const;
	
private:
	int m_SoundID;
};

}
