#include "PG/internal/platform/WinPlatformServices.h"

#include <Windows.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
void WinPlatformServices::exitApp()
{
	ExitProcess(0);
}

}
}