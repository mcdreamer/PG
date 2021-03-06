#pragma once

#include "PG/core/KeyCode.h"

namespace PG {

struct PhysicsBody;

//--------------------------------------------------------
class PhysicsBodyInputHandler
{
public:
	PhysicsBodyInputHandler(PhysicsBody& body)
	: m_Body(body)
	{}
	
	void keyDown(PG::KeyCode code, PG::KeyModifier mods);
	void keyUp(PG::KeyCode code);
	
private:
	PhysicsBody& m_Body;
	
	void handleHorizontalMovement(PG::KeyCode code, bool isMoving);
	void handleNonFreeVerticalMovement(PG::KeyCode code, bool isMoving);
	void handleFreeVerticalMovement(PG::KeyCode code, bool isMoving);
};

}
