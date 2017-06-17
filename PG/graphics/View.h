#pragma once

#include "PG/graphics/Scene.h"

#include <memory>

namespace PG {

//--------------------------------------------------------
class IView
{
public:
    virtual ~IView() {}
	
	virtual SceneControllerHandle presentScene(SceneControllerPtr& sceneController)=0;
};

}
