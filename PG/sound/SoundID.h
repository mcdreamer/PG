#pragma once

namespace PG {

//--------------------------------------------------------
class SoundID
{
public:
	SoundID()
	: m_SoundID(-1)
	{}

	explicit SoundID(int soundID)
	: m_SoundID(soundID)
	{}
	
	bool operator==(const SoundID& other) const;
	bool operator<(const SoundID& other) const;
	
	bool isValid() const { return m_SoundID != -1; }
	
private:
	int m_SoundID;
};

}
