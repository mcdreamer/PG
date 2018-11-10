#include "PG/internal/platform/WinPlatformServices.h"

#include <Windows.h>
#include <Shlwapi.h>

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

//--------------------------------------------------------
std::string WinPlatformServices::getResourcesFilePath()
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);

	std::wstring wPath(path);
	std::string ss(wPath.begin(), wPath.end());

	auto filenameStart = ss.find_last_of("\\");
	if (filenameStart == std::string::npos)
	{
		return "";
	}

	return ss.substr(0, filenameStart);
}


}
}
