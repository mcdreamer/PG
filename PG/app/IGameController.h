#pragma once

#include <string>

namespace PG {

class IPlatformServices;
class IView;
class IResourceHandler;
struct AppConfiguration;

//--------------------------------------------------------
class IGameController
{
public:
    virtual ~IGameController() {}
    
    virtual void start(IPlatformServices& platformServices,
                       IView& view,
                       IResourceHandler& resourceHandler)=0;
	
	virtual void				updateFinished()=0;
	
    virtual AppConfiguration	getConfiguration()=0;
};

}
