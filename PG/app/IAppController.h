#pragma once

namespace PG {

//--------------------------------------------------------
class IAppController
{
public:
    virtual ~IAppController() {}
    
    virtual void exitApp()=0;
};

}
