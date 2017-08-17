#pragma once

#include "PG/core/ValueRange.h"

#include <string>

namespace PG {

//--------------------------------------------------------
struct Sound
{
	std::string			resourceName;
	
	double				pitchScale = 1.0; //!< scale pitch of sound
	double				volume = 100.0; //!< volume range is 0 - 100
	
	ValueRange<double>	pitchScaleDeltaRange = ValueRange<double>(1.0, 1.0);
	ValueRange<double>	volumnDeltaRange = ValueRange<double>(0.0, 0.0);
};

}
