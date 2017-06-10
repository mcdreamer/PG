#pragma once

#include <string>

namespace PG {

//--------------------------------------------------------
class IResourceHandler
{
public:
    virtual ~IResourceHandler() {}

    virtual std::string getResourcePath(const std::string& name, const std::string& type)=0;
};

}
