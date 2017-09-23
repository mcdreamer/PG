#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBody.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyDown(PG::KeyCode code, PG::KeyModifier mods)
{
	if (code == PG::KeyCode::kRight)
	{
		m_Body.movingRight = true;
	}
	else if (code == PG::KeyCode::kLeft)
	{
		m_Body.movingLeft = true;
	}
	else if (code == PG::KeyCode::kUp && m_Body.onGround)
	{
		m_Body.jumpToConsume = true;
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyUp(PG::KeyCode code)
{
	if (code == PG::KeyCode::kRight)
	{
		m_Body.movingRight = false;
	}
	else if (code == PG::KeyCode::kLeft)
	{
		m_Body.movingLeft = false;
	}
}

}
