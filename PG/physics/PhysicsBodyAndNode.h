#pragma once

#include "PG/physics/PhysicsBody.h"
#include "PG/graphics/Node.h"

namespace PG {

//--------------------------------------------------------
struct PhysicsBodyAndNode
{
	PhysicsBodyAndNode(const PGRect& bodyRect)
	: body(bodyRect)
	{}

	PhysicsBody	body;
	NodeHandle	node;
};

}
