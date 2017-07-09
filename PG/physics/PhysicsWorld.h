#pragma once

#include "PG/core/Size.h"
#include "PG/data/DataGrid.h"
#include "PG/physics/PhysicsWorldParams.h"

namespace PG {

struct PhysicsBody;
class INode;

//--------------------------------------------------------
class PhysicsWorldCallback
{
public:
    virtual ~PhysicsWorldCallback () {}
    
    virtual void bodiesDidCollide(const PhysicsBody& bodyOne, const PhysicsBody& bodyTwo)=0;
};

//--------------------------------------------------------
class PhysicsWorld
{
public:
    PhysicsWorld(const PhysicsWorldParams& params, PhysicsWorldCallback& callback)
    : m_Params(params), m_Callback(callback)
    {}
    
    void						applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry, float dt) const;
    const PhysicsWorldParams&   getParams() const { return m_Params; }
    
private:
    PhysicsWorldParams			m_Params;
    PhysicsWorldCallback&		m_Callback;
};

}
