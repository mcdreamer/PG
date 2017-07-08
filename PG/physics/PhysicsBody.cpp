#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsWorld.h"
#include "PG/core/PointUtils.h"
#include "PG/core/SizeUtils.h"
#include "PG/core/MathsUtils.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBody::setPosition(const PGPoint& newPosition)
{
	bounds.origin = newPosition;
}

//--------------------------------------------------------
void PhysicsBody::hasHitGround()
{
	onGround = true;
}

//--------------------------------------------------------
void PhysicsBody::updateInWorld(const PhysicsWorld& world, float dt)
{
    const auto gravityStep = SizeUtils::scaleSize(world.getGravity(), dt);

	// Physics world constants
    const auto forward = PGPoint(2500, 0);
    const auto jumpForce = PGPoint(0, -70);

    const auto minMovement = PGPoint(-300, -4850);
    const auto maxMovement = PGPoint(300, 1000);

    const double friction = 0.84;
	
	

    auto forwardStep = PointUtils::scalePoint(forward, dt);

    // Gravity and X friction
    velocity = PointUtils::addToPoint(velocity, gravityStep);
    velocity = PGPoint(velocity.x * friction, velocity.y);


	// Modify state
    if (jumpToConsume && onGround)
    {
        velocity = PointUtils::addPoints(velocity, jumpForce);
		jumpToConsume = false;
    }

    if (movingRight)
    {
        velocity = PointUtils::addPoints(velocity, forwardStep);
    }

    if (movingLeft)
    {
        velocity = PointUtils::subtractPoints(velocity, forwardStep);
    }
	
	

    // Clamp velocity
    auto clampedVelX = MathsUtils::clamp(velocity.x, minMovement.x, maxMovement.x);
    auto clampedVelY = MathsUtils::clamp(velocity.y, minMovement.y, maxMovement.y);
    velocity = PGPoint(clampedVelX, clampedVelY);



    // Apply velocity
    auto velocityStep = PointUtils::scalePoint(velocity, dt);
    desiredPosition = PointUtils::addPoints(bounds.origin, velocityStep);
}

}
