#pragma once

#include "PG/core/ValueRange.h"

#include <string>

namespace PG {

//--------------------------------------------------------
struct Sound
{
	Sound()
	{}

	Sound(const std::string& resourceName_)
	: resourceName(resourceName_)
	{}

	std::string			resourceName;
	
	ValueRange<float>	pitchRange = ValueRange<float>(1.0f, 1.0f); //!< 1 = normal speed
	ValueRange<float>	volumeRange = ValueRange<float>(100.0f, 100.0f); //!< 0 to 100
};

}
