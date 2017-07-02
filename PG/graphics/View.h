#pragma once

#include "PG/graphics/Scene.h"

#include <memory>

namespace PG {

//--------------------------------------------------------
class IView
{
public:
    virtual ~IView() {}
	
	virtual SceneControllerHandle	replaceScene(SceneControllerPtr& sceneController)=0;
	virtual SceneControllerHandle	pushScene(SceneControllerPtr& sceneController)=0;
	virtual void					popScene()=0;
	
	virtual SceneControllerHandle	addOverlay(SceneControllerPtr& sceneController)=0;
	virtual void					removeOverlay(const SceneControllerHandle& sceneController)=0;
};

}
