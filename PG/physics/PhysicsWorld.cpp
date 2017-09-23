#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/app/GameConstants.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/RectUtils.h"
#include "PG/core/PointUtils.h"
#include "PG/core/SizeUtils.h"
#include "PG/core/MathsUtils.h"

#include <array>

namespace PG {

namespace
{
	const size_t kNumCoordsToTest = 9;
	using TileCoordsToTest = std::array<TileCoord, kNumCoordsToTest>;
	
	//--------------------------------------------------------
	TileCoordsToTest getCollisionTestCoords(const TileCoord& bodyTileCoord)
	{
		TileCoordsToTest coordsToTest;
		
		for (auto& coordToTest : coordsToTest)
		{
			coordToTest = bodyTileCoord;
		}
		
		auto coordToTestIt = coordsToTest.begin();
		
		// Aligned points
		++coordToTestIt;
		coordToTestIt->y -= 1;
		
		++coordToTestIt;
		coordToTestIt->y += 1;
		
		++coordToTestIt;
		coordToTestIt->x -= 1;
		
		++coordToTestIt;
		coordToTestIt->x += 1;
		
		// Diagonal points
		++coordToTestIt;
		coordToTestIt->x -= 1;
		coordToTestIt->y += 1;
		
		++coordToTestIt;
		coordToTestIt->x += 1;
		coordToTestIt->y += 1;
		
		++coordToTestIt;
		coordToTestIt->x -= 1;
		coordToTestIt->y -= 1;
		
		++coordToTestIt;
		coordToTestIt->x += 1;
		coordToTestIt->y -= 1;
		
		return coordsToTest;
	}

	// Don't allow passing through tiles
	// Better detection of whether collision is above/below or left/right?
	
    //--------------------------------------------------------
    void findIntersectionAndResolveForBody(PhysicsBody& body, const Rect& geometryRect)
    {
		const Rect desiredRect(body.desiredPosition, body.bounds.size);
		
		const auto intersection = RectUtils::getIntersection(desiredRect, geometryRect);
		if (!RectUtils::isEmpty(intersection))
		{
			Point removeIntersectionPt;
			Point adjustedVelocity;
			
			if (intersection.size.height < intersection.size.width)
			{
				const bool collisionBelow = (desiredRect.origin.y <= geometryRect.origin.y);
				if (collisionBelow)
				{
					body.hasHitGround();
				}
				
				const int dir = collisionBelow ? -1 : 1;
				removeIntersectionPt = Point(0, dir * intersection.size.height);
				adjustedVelocity = Point(body.velocity.x, 0);
			}
			else
			{
				const int dir = (desiredRect.origin.x < geometryRect.origin.x) ? -1 : 1;
				removeIntersectionPt = Point(dir * intersection.size.width, 0);
				adjustedVelocity = Point(0, body.velocity.y);
			}
			
			body.velocity = adjustedVelocity;
			body.desiredPosition = PointUtils::addPoints(body.desiredPosition, removeIntersectionPt);
		}
    }
	
    //--------------------------------------------------------
    void resolveCollisionAtCoord(const TileCoord& coordToTest, const DataGrid<bool>& levelGeometry, PhysicsBody& body)
    {
		if (coordToTest.x < 0
			|| coordToTest.x >= levelGeometry.getWidth()
			|| coordToTest.y < 0
			|| coordToTest.y >= levelGeometry.getHeight()
			|| !levelGeometry.at(coordToTest.x, coordToTest.y))
		{
			return;
		}
	
		TilePositionCalculator tilePosCalc;
		const Rect tileRect(tilePosCalc.calculatePoint(coordToTest), Size(GameConstants::tileSize(), GameConstants::tileSize()));

		findIntersectionAndResolveForBody(body, tileRect);
    }
	
	//--------------------------------------------------------
	void applyForcesToBody(PhysicsBody& body, const PhysicsWorldParams& params, float dt)
	{
		const auto gravityStep = SizeUtils::scaleSize(params.gravity, dt);
		const auto forwardStep = PointUtils::scalePoint(params.forward, dt);
		
		// Gravity and X friction
		body.velocity = PointUtils::addToPoint(body.velocity, gravityStep);
		body.velocity = Point(body.velocity.x * params.friction, body.velocity.y);
		
		// Modify state
		if (body.jumpToConsume && body.onGround)
		{
			body.velocity = PointUtils::addPoints(body.velocity, params.jumpForce);
			body.jumpToConsume = false;
			body.onGround = false;
		}
		
		if (body.movingRight)
		{
			body.velocity = PointUtils::addPoints(body.velocity, forwardStep);
		}
		
		if (body.movingLeft)
		{
			body.velocity = PointUtils::subtractPoints(body.velocity, forwardStep);
		}
		
		// Clamp velocity
		auto clampedVelX = MathsUtils::clamp(body.velocity.x, params.minMovement.x, params.maxMovement.x);
		auto clampedVelY = MathsUtils::clamp(body.velocity.y, params.minMovement.y, params.maxMovement.y);
		body.velocity = Point(clampedVelX, clampedVelY);
		
		// Apply velocity
		auto velocityStep = PointUtils::scalePoint(body.velocity, dt);
		body.desiredPosition = PointUtils::addPoints(body.bounds.origin, velocityStep);
	}
}

//--------------------------------------------------------
void PhysicsWorld::applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry, float dt) const
{
	applyForcesToBody(body, m_Params, dt);
	
	TilePositionCalculator tilePosCalc;
	const auto bodyTileCoord = tilePosCalc.calculateTileCoord(body.desiredPosition);
	
    // Collision detection
    const auto coordsToTest = getCollisionTestCoords(bodyTileCoord);
    for (size_t i = 0; i < coordsToTest.size(); ++i)
    {
        resolveCollisionAtCoord(coordsToTest[i], levelGeometry, body);
    }
    
    // Apply updated desired position
    body.setPosition(body.desiredPosition);
}

//--------------------------------------------------------
void PhysicsWorld::findCollisionsWithBody(const PhysicsBody& body,
										  const std::vector<PhysicsBody>& bodiesToCheck,
										  PhysicsWorldCallback& callback) const
{
	for (size_t nthBody = 0; nthBody < bodiesToCheck.size(); ++nthBody)
	{
		if (!RectUtils::isEmpty(RectUtils::getIntersection(body.bounds, bodiesToCheck[nthBody].bounds)))
		{
			callback.bodiesDidCollide(body, bodiesToCheck[nthBody], (int)nthBody);
		}
	}
}

}
