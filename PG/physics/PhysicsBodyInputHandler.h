#pragma once

#include "PG/core/PGKeyCode.h"

namespace PG {

struct PhysicsBody;

//--------------------------------------------------------
class PhysicsBodyInputHandler
{
public:
	PhysicsBodyInputHandler(PhysicsBody& body)
	: m_Body(body)
	{}
	
	void keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods);
	void keyUp(PG::PGKeyCode code);
	
private:
	PhysicsBody& m_Body;
};

}
