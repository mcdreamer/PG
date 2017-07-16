#pragma once

#include "PG/core/Point.h"
#include "PG/core/Size.h"
#include "PG/core/Rect.h"
#include "PG/core/Colour.h"

#include <memory>
#include <string>
#include <vector>

namespace PG {

//--------------------------------------------------------
enum class NodeType
{
    kNode,
    kSprite,
    kText,
    kParticle
};

class INode;

//--------------------------------------------------------
struct NodeHandle
{
    NodeHandle()
    : node(nullptr)
    {}

    NodeHandle(INode* node_)
    : node(node_)
    {}
    
    INode* node;
};

//--------------------------------------------------------
class INode
{
public:
    virtual ~INode() {}

	virtual void                setPosition(PGPoint point) = 0;
	virtual void                setSize(PGSize size) = 0;

    virtual NodeType            getType() const=0;

    virtual PGPoint             getPosition() const=0;
    virtual PGSize              getSize() const=0;
    virtual PGRect              getRect() const=0;
    
    virtual NodeHandle          addChild(std::unique_ptr<INode>& node)=0;
    virtual std::vector<INode*> getChildren()=0;
    virtual void                clearChildren()=0;

    virtual void                addUserData(const std::string& key, const std::string& value)=0;
    virtual void                addUserData(const std::string& key, const void* value)=0;
    virtual void                addUserDataInt(const std::string& key, const int value)=0;

    virtual std::string         getUserDataString(const std::string& key) const=0;
    virtual void*               getUserDataPtr(const std::string& key) const=0;
    virtual int                 getUserDataInt(const std::string& key) const=0;
    
    virtual void                removeFromParent()=0;
    
	virtual std::vector<INode*> findNodesAtPoint(double x, double y) = 0;
    
    virtual void                setText(const std::string& text)=0;
    
    virtual void                setColour(const Colour& colour)=0;
    virtual void                removeColour()=0;
};

using NodePtr = std::unique_ptr<INode>;
using NodePtrArray = std::vector<NodePtr>;

}
