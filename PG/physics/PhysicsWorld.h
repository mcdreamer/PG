#pragma once

#include "Size.h"

namespace PG {

struct PhysicsBody;
class INode;

//--------------------------------------------------------
class PhysicsWorldCallback
{
public:
    virtual ~PhysicsWorldCallback () {}
    
    virtual void bodiesDidCollide(PhysicsBody* bodyOne, PhysicsBody* bodyTwo)=0;
};

//--------------------------------------------------------
class PhysicsWorld
{
public:
    PhysicsWorld(const PGSize& gravity, PhysicsWorldCallback& callback)
    : m_Gravity(gravity), m_Callback(callback)
    {}
    
    void applyPhysicsForBody(PhysicsBody* body, INode* node, INode& parent) const;
    
    const PGSize&           getGravity() const { return m_Gravity; }
    
private:
    PGSize                  m_Gravity;
    PhysicsWorldCallback&   m_Callback;
};

}
