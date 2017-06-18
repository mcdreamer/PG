#include "PG/internal/platform/WinResourceHandler.h"
#include "PG/internal/platform/ResourceHandler.h"

#include <string>
#include <iostream>

#include <Windows.h>
#include <Shlwapi.h>

namespace PG {
namespace Internal {

//--------------------------------------------------------
std::string WinResourceHandler::getResourcePath(const std::string& name, const std::string& type)
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

	ResourceHandler rh;
	return rh.getResourcePath(ss.substr(0, filenameStart), name, type);
}

//--------------------------------------------------------
namespace WinResourceHandlerUtils {

std::string getResourcePath(const std::string& name, const std::string& type)
{
	WinResourceHandler resHandler;
	return resHandler.getResourcePath(name, type);
}

};

}
}
