#include "PhysicsTests.h"
#include "gtest/gtest.h"

#include "PG/physics/PhysicsWorld.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/app/GameConstants.h"
#include "PG/entities/TilePositionCalculator.h"

using namespace PG;

//--------------------------------------------------------
class TestPhysicsWorldCallback : public PhysicsWorldCallback
{
public:
	virtual void bodiesDidCollide(const PhysicsBody& bodyOne, const PhysicsBody& bodyTwo) override {}
};

//--------------------------------------------------------
TEST(PhysicsTests,testPhysicsWorld)
{
	TestPhysicsWorldCallback worldCallback;
	PhysicsWorld world(PGSize(0, -10), worldCallback);

	DataGrid<bool> levelGeometry(10, 10);
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			levelGeometry.set(x, y, y == 5);
		}
	}
	
	TilePositionCalculator tilePosCalc;
	
	PhysicsBody body(PGRect(tilePosCalc.calculatePoint(TileCoord(5, 8)), PGSize(GameConstants::tileSize(), GameConstants::tileSize())));
	
//	for (int i = 0; i < 10; ++i)
//	{
		const auto posBeforeUpdate = body.desiredPosition;
		body.updateInWorld(world, 0.1);
		
		const auto posAfterUpdate = body.desiredPosition;
		EXPECT_NE(posAfterUpdate, posBeforeUpdate);
		
		world.applyPhysicsForBody(body, levelGeometry);
		
		EXPECT_EQ(body.bounds.origin, posAfterUpdate);
//	}
}
