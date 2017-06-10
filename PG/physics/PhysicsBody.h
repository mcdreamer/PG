#pragma once

#include "PG/core/Point.h"
#include "PG/core/Rect.h"

namespace PG {

class PhysicsWorld;

//--------------------------------------------------------
struct PhysicsBody
{
    PGRect      bounds;
    PGPoint     velocity;
    PGPoint     desiredPosition;
    
    void updateInWorld(PhysicsWorld* world, float dt, PGPoint currPos);
    void hasHitGround(bool hitGround);
};

}
