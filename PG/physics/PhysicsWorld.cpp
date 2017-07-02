#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/app/GameConstants.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/PGRectUtils.h"
#include "PG/core/PointUtils.h"

#include <array>

namespace PG {

namespace
{
	const size_t kNumCoordsToTest = 9;
	using TileCoordsToTest = std::array<TileCoord, kNumCoordsToTest>;

    //--------------------------------------------------------
    void getCollisionTestCoords(TileCoordsToTest& coordsToTest, const TileCoord& bodyTileCoord)
    {
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
    }
    
    //--------------------------------------------------------
    void findIntersectionAndResolveForBody(PhysicsBody& body, const PGRect& geometryRect)
    {
		const PGRect desiredRect(body.desiredPosition, body.bounds.size);
		
		auto intersection = PGRectUtils::getIntersection(desiredRect, geometryRect);
		if (!PGRectUtils::isEmpty(intersection))
		{
			PGPoint removeIntersectionPt;
			PGPoint adjustedVelocity;
			
			if (intersection.size.height < intersection.size.width)
			{
				bool collisionBelow = (geometryRect.origin.y < desiredRect.origin.y);
				if (collisionBelow)
				{
					body.hasHitGround();
				}
				
				int dir = collisionBelow ? 1 : -1;
				removeIntersectionPt = PGPoint(0, dir * intersection.size.height);
				adjustedVelocity = PGPoint(body.velocity.x, collisionBelow ? 0 : -100); // enough force not to stick when hitting top
			}
			else
			{
				int dir = (geometryRect.origin.x < desiredRect.origin.x) ? 1 : -1;
				removeIntersectionPt = PGPoint(dir * intersection.size.width, 0);
				adjustedVelocity = PGPoint(0, body.velocity.y);
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
		const PGRect tileRect(tilePosCalc.calculatePoint(coordToTest), PGSize(GameConstants::tileSize(), GameConstants::tileSize()));

		findIntersectionAndResolveForBody(body, tileRect);
    }
}

//--------------------------------------------------------
void PhysicsWorld::applyPhysicsForBody(PhysicsBody& body, const DataGrid<bool>& levelGeometry) const
{
	TilePositionCalculator tilePosCalc;
	const auto bodyTileCoord = tilePosCalc.calculateTileCoord(body.desiredPosition);
    
    // Collision detection
    TileCoordsToTest coordsToTest;
    getCollisionTestCoords(coordsToTest, bodyTileCoord);
    for (size_t i = 0; i < coordsToTest.size(); ++i)
    {
        resolveCollisionAtCoord(coordsToTest[i], levelGeometry, body);
    }
    
    // Apply updated desired position
    body.setPosition(body.desiredPosition);
}

}
