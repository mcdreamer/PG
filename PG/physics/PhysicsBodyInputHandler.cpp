#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBody.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods)
{
	if (code == PG::PGKeyCodeRight)
	{
		m_Body.movingRight = true;
	}
	else if (code == PG::PGKeyCodeLeft)
	{
		m_Body.movingLeft = true;
	}
	else if (code == PG::PGKeyCodeUp)
	{
		m_Body.jumpToConsume = true;
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyUp(PG::PGKeyCode code)
{
	if (code == PG::PGKeyCodeRight)
	{
		m_Body.movingRight = false;
	}
	else if (code == PG::PGKeyCodeLeft)
	{
		m_Body.movingLeft = false;
	}
}

}
