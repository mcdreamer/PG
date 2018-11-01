#pragma once

#include <string>

namespace PG {

//--------------------------------------------------------
struct ResourceData
{
    const char* data = nullptr;
    size_t size = 0;
};

//--------------------------------------------------------
class IResourceHandler
{
public:
    virtual ~IResourceHandler() {}

    virtual ResourceData getResourceData(const std::string& resourcePath)=0;
};

}
