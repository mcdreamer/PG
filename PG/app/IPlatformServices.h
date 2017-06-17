#pragma once

namespace PG {

//--------------------------------------------------------
class IPlatformServices
{
public:
    virtual ~IPlatformServices() {}
    
    virtual void exitApp()=0;
};

}
