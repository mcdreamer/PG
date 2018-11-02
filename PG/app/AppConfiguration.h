#pragma once

#include "PG/app/StyleSheet.h"
#include "PG/core/Size.h"

#include <string>

namespace PG {
	
//--------------------------------------------------------
struct AppConfiguration
{
	std::string	windowTitle;
	Size		windowSize;
	
	int			tileSize = 32;
	
	std::string	resourcesFilename;
	StyleSheet	styleSheet;
};

}
