#include "PG/internal/platform/ResourceHandler.h"

#include <boost/algorithm/string.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
std::string ResourceHandler::getResourcePath(const std::string& exeDir,
                                             const std::string& name,
                                             const std::string& type)
{
  std::string baseDir = exeDir + "/resources/";

	auto nameToUse = name;
	boost::replace_all(nameToUse, type, "");
	boost::replace_all(nameToUse, ".", "");

	if (boost::iequals(type, "png"))
	{
		return baseDir + "images/" + nameToUse + ".png";
	}
	else if (boost::iequals(type, "ttf"))
	{
		return baseDir + "fonts/" + nameToUse + ".ttf";
	}
	else
	{
		return baseDir + "data/" + nameToUse + ".json";
	}
}

}
}
