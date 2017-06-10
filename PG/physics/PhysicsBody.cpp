#include "PG/physics/PhysicsBody.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBody::updateInWorld(PhysicsWorld* world, float dt, PGPoint currPos)
{
//    auto gravityStep = PGPointScale(world->getGravity(), dt);
//
//    auto forward = PGPoint(2500, 0);
//    auto jumpForce = PGPoint(0, 700);
//    auto jumpPadForce = PGPoint(0, 900);
//
//    auto minMovement = PGPoint(-300, -4850);
//    auto maxMovement = PGPoint(300, 1000);
//
//    double friction = 0.84;
//
//    auto forwardStep = PGPointScale(forward, dt);
//
//    // Gravity and X friction
//    velocity = PGPointAdd(velocity, gravityStep);
//    velocity = PGPoint(velocity.x * friction, velocity.y);
//
//    if (state->jumpToConsume && onGround)
//    {
//        velocity = PGPointAdd(velocity, jumpForce);
//    }
//
//    if (state->jumpPadToConsume && onGround)
//    {
//        velocity = PGPointAdd(velocity, jumpPadForce);
//    }
//
//    if (state->movingRight)
//    {
//        velocity = PGPointAdd(velocity, forwardStep);
//    }
//
//    if (state->movingLeft)
//    {
//        velocity = PGPointSubtract(velocity, forwardStep);
//    }
//
//    // Clamp velocity
//    auto clampedVelX = MathsUtils::clamp(velocity.x, minMovement.x, maxMovement.x);
//    auto clampedVelY = MathsUtils::clamp(velocity.y, minMovement.y, maxMovement.y);
//    velocity = PGPoint(clampedVelX, clampedVelY);
//
//    // Apply velocity
//    auto velocityStep = PGPointScale(velocity, dt);
//    desiredPosition = PGPointAdd(currPos, velocityStep);
}

}
