#pragma once

#include "PG/io/IResourceHandler.h"

#include <string>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class WinResourceHandler : public IResourceHandler
{
public:
	virtual std::string getResourcePath(const std::string& name, const std::string& type) override;
};

//--------------------------------------------------------
namespace WinResourceHandlerUtils
{
	std::string getResourcePath(const std::string& name, const std::string& type);
};

}
}