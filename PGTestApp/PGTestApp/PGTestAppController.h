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
    
    virtual void					start(PG::AppHostServices& appHostServices, PG::IView& view) override;	
	virtual void					updateFinished() override;
    virtual PG::AppConfiguration	getConfiguration() override;
	
	virtual bool 					receiveTag(const int tag) override;
	
private:
    PG::AppHostServices*			m_AppHostServices;
    PG::IView*						m_View;
	PG::AppConfiguration			m_AppConfig;
	
	void							initialiseConfig();
};
