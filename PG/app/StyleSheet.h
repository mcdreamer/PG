#pragma once

#include "PG/core/Colour.h"

#include <string>

namespace PG {

//--------------------------------------------------------
struct StyleSheet
{
	std::string	uiFontName;
	
	double		buttonFontSize = 30.0;
	Colour		buttonBackgroundColour;
	Colour		buttonTextColour;
	double		buttonPadding = 4.0;

};

}
