#include "PG/physics/PhysicsBody.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBody::setPosition(const Point& newPosition)
{
	bounds.origin = newPosition;
}

//--------------------------------------------------------
void PhysicsBody::hasHitGround()
{
	onGround = true;
}

}
