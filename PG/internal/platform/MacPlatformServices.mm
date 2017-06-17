#include "PG/internal/platform/MacPlatformServices.h"

#import <AppKit/AppKit.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
void MacPlatformServices::exitApp()
{
    [NSApp terminate:nil];
}

}
}
