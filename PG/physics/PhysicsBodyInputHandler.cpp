#include "PG/physics/PhysicsBodyInputHandler.h"
#include "PG/physics/PhysicsBody.h"

namespace PG {

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyDown(PG::KeyCode code, PG::KeyModifier mods)
{
	handleHorizontalMovement(code, true);
	
	if (!m_Body.isFreeMoving)
	{
		handleNonFreeVerticalMovement(code, true);
	}
	else
	{
		handleFreeVerticalMovement(code, true);
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::keyUp(PG::KeyCode code)
{
	handleHorizontalMovement(code, false);
	
	if (!m_Body.isFreeMoving)
	{
		handleNonFreeVerticalMovement(code, false);
	}
	else
	{
		handleFreeVerticalMovement(code, false);
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::handleHorizontalMovement(PG::KeyCode code, bool isMoving)
{
	switch (code)
	{
		case PG::KeyCode::kRight:
			m_Body.movingRight = isMoving;
			break;
		case PG::KeyCode::kLeft:
			m_Body.movingLeft = isMoving;
			break;
		default:
			break;
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::handleNonFreeVerticalMovement(PG::KeyCode code, bool isMoving)
{
	if (isMoving && code == PG::KeyCode::kUp && m_Body.onGround)
	{
		m_Body.jumpToConsume = true;
	}
}

//--------------------------------------------------------
void PhysicsBodyInputHandler::handleFreeVerticalMovement(PG::KeyCode code, bool isMoving)
{
	switch (code)
	{
		case PG::KeyCode::kUp:
			m_Body.movingUp = isMoving;
			break;
		case PG::KeyCode::kDown:
			m_Body.movingDown = isMoving;
			break;
		default:
			break;
	}
}

}
