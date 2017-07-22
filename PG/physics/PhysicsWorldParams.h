#pragma once

#include "PG/core/Point.h"
#include "PG/core/Size.h"

namespace PG {

//--------------------------------------------------------
struct PhysicsWorldParams
{
	Size gravity = Size(0, 10);

	Point forward = Point(2500, 0);
	Point jumpForce = Point(0, -100);

	Point minMovement = Point(-300, -4850);
	Point maxMovement = Point(300, 1000);

	double friction = 0.84;
};

}
