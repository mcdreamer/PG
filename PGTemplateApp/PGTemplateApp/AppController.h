#pragma once

#include "PG/core/Size.h"
#include "PG/app/IGameController.h"
#include "PG/app/AppConfiguration.h"

//--------------------------------------------------------
class AppController : public PG::IGameController
{
public:
    AppController();
    ~AppController();
    
    virtual void					start(PG::AppHostServices& appHostServices, PG::IView& view) override;	
	virtual void					updateFinished() override;
    virtual PG::AppConfiguration	getConfiguration() override;
	
private:
    PG::AppHostServices*			m_AppHostServices;
    PG::IView*						m_View;
	PG::AppConfiguration			m_AppConfig;
	
	void							initialiseConfig();
};
