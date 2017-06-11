#pragma once

#include "PG/core/Size.h"
#include "PG/app/IGameController.h"
#include "PG/app/AppConfiguration.h"

#include <memory>

namespace PG {
    
class IAppController;
class IViewHandle;
class IResourceHandler;
class ISceneCallback;

}

//--------------------------------------------------------
class ISceneTransitionHelper
{
public:
	virtual ~ISceneTransitionHelper() {}
	
	virtual void scheduleScene()=0;
};

//--------------------------------------------------------
class PGTestAppController : public PG::IGameController, public ISceneTransitionHelper
{
public:
    PGTestAppController();
    ~PGTestAppController();
    
    virtual void start(PG::IAppController& appController,
                       PG::IViewHandle& viewHandle,
                       PG::IResourceHandler& resourceHandler) override;
	
	virtual void updateFinished() override;
	
    virtual PG::AppConfiguration			getConfiguration() override;
    
private:
    PG::IAppController*                     m_AppController;
    PG::IViewHandle*                        m_ViewHandle;
    PG::IResourceHandler*                   m_ResourceHandler;
	PG::AppConfiguration					m_AppConfig;
	
    std::unique_ptr<PG::ISceneCallback>		m_SceneCallback;
	
	void									initialiseConfig();
	
	bool	m_RunNextScene;
	
	virtual void scheduleScene() override;
};
