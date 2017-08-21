#include "PG/internal/platform/WinPlatformServices.h"

#include <Windows.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
void WinPlatformServices::exitApp()
{
	ExitProcess(0);
}

//--------------------------------------------------------
float WinPlatformServices::getDisplayScale()
{
	return 1.0f;
}

}
}
