#pragma once

#include "PG/io/IResourceHandler.h"

#include <string>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class LinuxResourceHandler : public IResourceHandler
{
public:
	virtual std::string getResourcePath(const std::string& name, const std::string& type) override;
};

}
}
