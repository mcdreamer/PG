#include "PG/internal/platform/WinResourceHandler.h"

#include <boost/algorithm/string.hpp>

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

	std::string baseDir = ss.substr(0, filenameStart) + "\\resources\\";

	auto nameToUse = name;
	boost::replace_all(nameToUse, type, "");
	boost::replace_all(nameToUse, ".", "");

	if (boost::iequals(type, "png"))
	{
		return baseDir + "images\\" + nameToUse + ".png";
	}
	else if (boost::iequals(type, "ttf"))
	{
		return baseDir + "fonts\\" + nameToUse + ".ttf";
	}
	else
	{
		return baseDir + "data\\" + nameToUse + ".json";
	}
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