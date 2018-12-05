#pragma once

#include "PG/ui/TagReceiver.h"

#include <string>

namespace PG {

class AppHostServices;
class IView;
struct AppConfiguration;

//--------------------------------------------------------
class IGameController : public TagReceiver
{
public:
    virtual ~IGameController() {}
    
    virtual void start(AppHostServices& appHostServices,
                       IView& view)=0;
	
	virtual void				updateFinished()=0;
	
    virtual AppConfiguration	getConfiguration()=0;
};

}
