#pragma once

#include <string>

namespace PG {

class IAppController;
class IViewHandle;
class IResourceHandler;
class PGSize;

//--------------------------------------------------------
class IGameController
{
public:
    virtual ~IGameController() {}
    
    virtual void start(IAppController& appController,
                       IViewHandle& viewHandle,
                       IResourceHandler& resourceHandler)=0;
	
	virtual void updateFinished()=0;
	
    virtual std::string getWindowTitle()=0;
    virtual PGSize      getWindowSize()=0;
    virtual int         getTileSize()=0;
};

}
