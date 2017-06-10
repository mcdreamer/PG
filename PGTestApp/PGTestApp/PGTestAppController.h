#pragma once

#include "PG/core/Size.h"
#include "PG/app/IGameController.h"

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
	
    virtual std::string     getWindowTitle() override;
    virtual PG::PGSize      getWindowSize() override;
    virtual int             getTileSize() override;
    
private:
    PG::IAppController*                     m_AppController;
    PG::IViewHandle*                        m_ViewHandle;
    PG::IResourceHandler*                   m_ResourceHandler;
    
    std::unique_ptr<PG::ISceneCallback>		m_SceneCallback;
	
	bool	m_RunNextScene;
	
	virtual void scheduleScene() override;
};
