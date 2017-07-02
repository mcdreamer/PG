#pragma once

#include "PG/core/Size.h"
#include "PG/data/DataGrid.h"

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
    PhysicsWorld(const PGSize& gravity, PhysicsWorldCallback& callback)
    : m_Gravity(gravity), m_Callback(callback)
    {}
    
    void					applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry) const;
    const PGSize&           getGravity() const { return m_Gravity; }
    
private:
    PGSize                  m_Gravity;
    PhysicsWorldCallback&   m_Callback;
};

}
