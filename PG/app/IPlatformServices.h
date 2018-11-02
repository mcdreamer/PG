#pragma once

#include <string>

namespace PG {

//--------------------------------------------------------
class IPlatformServices
{
public:
    virtual ~IPlatformServices() {}
    
    virtual void		exitApp()=0;
	virtual float		getDisplayScale()=0;
	virtual std::string	getResourcesFilePath()=0;
};

}
