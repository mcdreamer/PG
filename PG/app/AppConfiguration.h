#pragma once

#include "PG/app/StyleSheet.h"
#include "PG/core/Size.h"

#include <string>

namespace PG {
	
//--------------------------------------------------------
struct AppConfiguration
{
	std::string	windowTitle;
	PGSize		windowSize;
	
	int			tileSize = 32;
	
	StyleSheet	styleSheet;
};

}
