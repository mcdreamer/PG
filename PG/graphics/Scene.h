#pragma once

#include "PG/core/KeyCode.h"
#include "PG/graphics/Node.h"

#include <memory>

namespace PG {

class IScene;
class ISceneController;
struct NodeHandle;
class UIElement;
class Colour;
class Size;
class Point;
struct StyleSheet;
class AppHostServices;
class Camera;

//--------------------------------------------------------
struct SceneHandle
{
	SceneHandle()
	: scene(nullptr)
	{}
	
	SceneHandle(IScene* scene_)
	: scene(scene_)
	{}
	
	IScene* scene;
};

//--------------------------------------------------------
struct SceneControllerHandle
{
	SceneControllerHandle()
	: controller(nullptr)
	{}
	
	SceneControllerHandle(ISceneController* controller_)
	: controller(controller_)
	{}
	
	ISceneController* controller;
};

//--------------------------------------------------------
class ISceneController
{
public:
    virtual ~ISceneController() {}
	
	virtual void	initScene(AppHostServices& appHostServices, SceneHandle scene)=0;
	
    virtual void    update(double dt)=0;
    
	virtual void    keyUp(KeyCode code)=0;
    virtual void    keyDown(KeyCode code, KeyModifier mods)=0;
	
	virtual void    clickInScene(Point pt, bool isRightClick)=0;
    virtual void    draggedWithOffset(Point pt)=0;
    virtual void    mouseMoved(Point pt)=0;
};

using SceneControllerPtr = std::unique_ptr<ISceneController>;

//--------------------------------------------------------
class IScene
{
public:
    virtual ~IScene() {}
	
	virtual Size					getSceneSize() const=0;
	virtual	SceneControllerHandle	getController() const=0;
	virtual NodeHandle				getRoot() const=0;
	virtual NodeHandle				getUIRoot() const=0;
	virtual const Colour			getBackgroundColour() const=0;
	virtual Point					getWindowPointAsScenePoint(const Point& windowPt, INode* layer) const=0;
	virtual Camera					getCamera() const=0;
	
	virtual NodeHandle				addChild(std::unique_ptr<INode>& node)=0;
	virtual void					pushUIElement(UIElement* uiElement)=0;
	virtual void					setBackgroundColour(const Colour& colour)=0;
	virtual void					setCamera(const Camera& camera)=0;
	
	virtual void					clickInScene(PG::Point pt, bool isRightClick)=0;
	
	virtual void					update(double dt)=0;
};

using ScenePtr = std::unique_ptr<IScene>;

//--------------------------------------------------------
class SceneCreator
{
public:
    static ScenePtr createScene(SceneControllerPtr& controller,
								AppHostServices& appHostServices,
								const Size& size);
};

}
