#pragma once

#include "PG/core/Point.h"
#include "PG/core/Size.h"

namespace PG {

//--------------------------------------------------------
struct PhysicsWorldParams
{
	PGSize gravity = PGSize(0, 10);

	PGPoint forward = PGPoint(2500, 0);
	PGPoint jumpForce = PGPoint(0, -100);

	PGPoint minMovement = PGPoint(-300, -4850);
	PGPoint maxMovement = PGPoint(300, 1000);

	double friction = 0.84;
};

}
