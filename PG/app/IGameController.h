#pragma once

#include <string>

namespace PG {

class IAppController;
class IViewHandle;
class IResourceHandler;
struct AppConfiguration;

//--------------------------------------------------------
class IGameController
{
public:
    virtual ~IGameController() {}
    
    virtual void start(IAppController& appController,
                       IViewHandle& viewHandle,
                       IResourceHandler& resourceHandler)=0;
	
	virtual void				updateFinished()=0;
	
    virtual AppConfiguration	getConfiguration()=0;
};

}
