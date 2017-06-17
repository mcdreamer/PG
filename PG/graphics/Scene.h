#pragma once

#include "PG/core/PGKeyCode.h"
#include "PG/graphics/Node.h"

#include <memory>

namespace PG {

class IScene;
class ISceneController;
struct NodeHandle;
class View;
class PGUIElement;
class Colour;
class PGSize;
class PGPoint;
struct StyleSheet;

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
	
	virtual void	initScene(SceneHandle scene)=0;
	
    virtual void    update(float dt)=0;
    
	virtual void    keyUp(PGKeyCode code)=0;
    virtual void    keyDown(PGKeyCode code, PGKeyModifier mods)=0;
	
	virtual void    clickInScene(PGPoint pt, bool isRightClick)=0;
    virtual void    draggedWithOffset(PGPoint pt)=0;
    virtual void    mouseMoved(PGPoint pt)=0;
};

using SceneControllerPtr = std::unique_ptr<ISceneController>;

//--------------------------------------------------------
class IScene
{
public:
    virtual ~IScene() {}
	
	virtual PGSize					getSceneSize() const=0;
	virtual const StyleSheet&		getStyleSheet() const=0;
	virtual	SceneControllerHandle	getController() const=0;
	virtual NodeHandle				getRoot() const=0;
	virtual const Colour			getBackgroundColour() const=0;
	virtual PGPoint					getWindowPointAsScenePoint(const PGPoint& windowPt, INode* layer) const=0;
	
	virtual NodeHandle				addChild(std::unique_ptr<INode>& node)=0;
	virtual void					pushUIElement(PGUIElement* uiElement)=0;
	virtual void					setBackgroundColour(const Colour& colour)=0;
	
	virtual void					clickInScene(PG::PGPoint pt, bool isRightClick)=0;
	
	virtual void					update(float dt)=0;
};

using ScenePtr = std::unique_ptr<IScene>;

//--------------------------------------------------------
class SceneCreator
{
public:
    static ScenePtr createScene(SceneControllerPtr& controller, const PGSize& size, const StyleSheet& styleSheet);
};

}
