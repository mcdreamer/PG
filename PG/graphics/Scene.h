#pragma once

#include "PG/core/PGKeyCode.h"

#include <memory>

namespace PG {

class INode;
struct NodeHandle;
class IViewHandle;
class ISceneCallback;
class PGUIElement;
class Colour;
class PGSize;
class PGPoint;
struct StyleSheet;

//--------------------------------------------------------
class ISceneCallback
{
public:
    virtual ~ISceneCallback() {}
    
    virtual void    update(float dt)=0;
    
    virtual void    keyDown(PGKeyCode code, PGKeyModifier mods)=0;
    virtual void    keyUp(PGKeyCode code)=0;
    virtual void    clickInWindow(PGPoint pt, bool isRightClick)=0;
    virtual void    draggedWithOffset(PGPoint pt)=0;
    virtual void    mouseMoved(PGPoint pt)=0;
};

//--------------------------------------------------------
class IScene
{
public:
    virtual ~IScene() {}
    
    virtual void				setBackgroundColour(const Colour& colour)=0;
	virtual void				presentSceneOnView(IViewHandle& view, ISceneCallback* sceneController)=0;
	virtual PGSize				getSceneSize() const=0;
	virtual const StyleSheet&	getStyleSheet() const=0;
	
	virtual NodeHandle			addChild(std::unique_ptr<INode>& node)=0;
	virtual void				pushUIElement(PGUIElement* uiElement)=0;
	
	virtual PGPoint				getWindowPointAsScenePoint(const PGPoint& windowPt, INode* layer) const=0;
};

using ScenePtr = std::unique_ptr<IScene>;

//--------------------------------------------------------
class SceneCreator
{
public:
    static ScenePtr createScene();
};

}
