#pragma once

#include "PG/core/Colour.h"

#include <string>

namespace PG {

//--------------------------------------------------------
struct StyleSheet
{
	std::string	uiFontName;
	
	Colour		buttonBackgroundColour;
	Colour		buttonTextColour;
	double		buttonPadding = 4.0;

};

}
