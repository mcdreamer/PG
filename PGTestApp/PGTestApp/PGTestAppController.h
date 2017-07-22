#pragma once

#include "PG/core/Size.h"
#include "PG/app/IGameController.h"
#include "PG/app/AppConfiguration.h"
#include "PG/ui/TagReceiver.h"

//--------------------------------------------------------
class PGTestAppController : public PG::IGameController, public PG::TagReciever
{
public:
    PGTestAppController();
    ~PGTestAppController();
    
    virtual void					start(PG::IPlatformServices& platformServices,
										  PG::IView& view,
										  PG::IResourceHandler& resourceHandler) override;	
	virtual void					updateFinished() override;
    virtual PG::AppConfiguration	getConfiguration() override;
	
	virtual void					receiveTag(const int tag, PG::UIMessageQueuePoster& msgPoster) override;
	
private:
    PG::IPlatformServices*			m_PlatformServices;
    PG::IView*						m_View;
    PG::IResourceHandler*           m_ResourceHandler;
	PG::AppConfiguration			m_AppConfig;
	
	void							initialiseConfig();
};
