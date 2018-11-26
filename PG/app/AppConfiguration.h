#pragma once

#include "PG/app/StyleSheet.h"
#include "PG/core/Size.h"

#include <string>

namespace PG {
	
class TagReceiver;
	
//--------------------------------------------------------
struct AppConfiguration
{
	AppConfiguration(TagReceiver* uiParent_)
	: uiParent(uiParent_)
	{}
	
	std::string		windowTitle;
	Size			windowSize;
	
	int				tileSize = 32;
	
	StyleSheet		styleSheet;
	
	TagReceiver*	uiParent;
};

}
