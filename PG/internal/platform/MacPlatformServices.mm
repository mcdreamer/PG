#include "PG/internal/platform/MacPlatformServices.h"

#import <AppKit/AppKit.h>

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

}
}
