#include "PG/sound/SoundID.h"

namespace PG {

//--------------------------------------------------------
bool SoundID::operator==(const SoundID& other) const
{
	return m_SoundID == other.m_SoundID;
}

//--------------------------------------------------------
bool SoundID::operator<(const SoundID& other) const
{
	return m_SoundID < other.m_SoundID;
}

}
