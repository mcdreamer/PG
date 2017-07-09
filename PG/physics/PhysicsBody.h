#pragma once

#include "PG/core/Point.h"
#include "PG/core/Rect.h"

namespace PG {

class PhysicsWorld;

//--------------------------------------------------------
struct PhysicsBody
{
	PhysicsBody(const PGRect bounds_)
	: bounds(bounds_),
	desiredPosition(bounds_.origin),
	jumpToConsume(false),
	onGround(false),
	movingLeft(false),
	movingRight(false)
	{}

	void		setPosition(const PGPoint& newPosition);
	void		hasHitGround();

    PGRect      bounds;
    PGPoint     velocity;
    PGPoint     desiredPosition;
	
	bool		jumpToConsume;
	bool		onGround;
	bool		movingLeft;
	bool		movingRight;
	
    void hasHitGround(bool hitGround);
};

}
