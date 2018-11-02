#include "PG/internal/platform/MacPlatformServices.h"

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
void MacPlatformServices::exitApp()
{
    [NSApp terminate:nil];
}

//--------------------------------------------------------
float MacPlatformServices::getDisplayScale()
{
	NSScreen* screen = [NSScreen mainScreen];
	if (screen)
	{
		return (float)[screen backingScaleFactor];
	}
	
	return 1.0f;
}
	
namespace
{
	//--------------------------------------------------------
	std::string nsStringToStdString(NSString* nsString)
	{
		return nsString ? [nsString UTF8String] : std::string();
	}
}

//--------------------------------------------------------
std::string MacPlatformServices::getResourcesFilePath()
{
	NSBundle* mainBundle = [NSBundle mainBundle];
	
	return nsStringToStdString([mainBundle resourcePath]);
}

}
}
