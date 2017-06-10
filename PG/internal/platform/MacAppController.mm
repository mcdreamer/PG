#include "MacAppController.h"

#import <AppKit/AppKit.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
void MacAppController::exitApp()
{
    [NSApp terminate:nil];
}

}
}
