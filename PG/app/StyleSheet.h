#pragma once

#include "PG/core/Colour.h"
#include "PG/core/Size.h"

#include <string>

namespace PG {

//--------------------------------------------------------
struct StyleSheet
{
	std::string	uiFontName;
	
	double		buttonFontSize = 30.0;
	Colour		buttonBackgroundColour = Colour::blue();
	Colour		buttonTextColour = Colour::white();
	double		buttonPadding = 4.0;
	
	double		dialogFontSize = 16.0;
	Size		dialogSize = Size(400, 300);
	Colour		dialogBackgroundColour = Colour::white();
	Colour		dialogTextColour = Colour::black();

};

}
