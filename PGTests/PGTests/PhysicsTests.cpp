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

namespace
{
	//--------------------------------------------------------
	struct TestWorld
	{
		TestWorld()
		: world(PhysicsWorldParams{}, worldCallback),
		levelGeometry(10, 10)
		{
			for (int y = 0; y < 10; ++y)
			{
				for (int x = 0; x < 10; ++x)
				{
					levelGeometry.set(x, y, y == 5);
				}
			}
		}
	
		TestPhysicsWorldCallback	worldCallback;
		PhysicsWorld				world;
		DataGrid<bool>				levelGeometry;
	};
}

//--------------------------------------------------------
TEST(PhysicsTests,testPhysicsWorld_Gravity)
{
	TestWorld testWorld;
	
	TilePositionCalculator tilePosCalc;
	
	PhysicsBody body(PGRect(tilePosCalc.calculatePoint(TileCoord(5, 0)), PGSize(GameConstants::tileSize(), GameConstants::tileSize())));
	
	const auto posBeforeUpdate = body.desiredPosition;
	
	testWorld.world.applyPhysicsForBody(body, testWorld.levelGeometry, 0.1);
	
	EXPECT_TRUE(body.bounds.origin.y > posBeforeUpdate.y);
}

//--------------------------------------------------------
TEST(PhysicsTests,testPhysicsWorld_RestingBody)
{
	TestWorld testWorld;
	
	TilePositionCalculator tilePosCalc;
	
	PhysicsBody body(PGRect(tilePosCalc.calculatePoint(TileCoord(5, 4)), PGSize(GameConstants::tileSize(), GameConstants::tileSize())));
	
	const auto posBeforeUpdate = body.desiredPosition;
	
	testWorld.world.applyPhysicsForBody(body, testWorld.levelGeometry, 0.1);
	
	EXPECT_EQ(body.bounds.origin, posBeforeUpdate);
}

//--------------------------------------------------------
TEST(PhysicsTests,testPhysicsWorld_BodyComingToRest)
{
	TestWorld testWorld;
	
	TilePositionCalculator tilePosCalc;
	
	const auto targetPt = tilePosCalc.calculatePoint(TileCoord(5, 4));
	PhysicsBody body(PGRect(targetPt, PGSize(GameConstants::tileSize(), GameConstants::tileSize())));
	body.bounds.origin.y -= 0.2;
	
	testWorld.world.applyPhysicsForBody(body, testWorld.levelGeometry, 0.1);
	
	EXPECT_NEAR(body.bounds.origin.y, targetPt.y - 0.1, 0.0001);
	
	testWorld.world.applyPhysicsForBody(body, testWorld.levelGeometry, 0.1);
	
	EXPECT_EQ(body.bounds.origin, targetPt);
	
	testWorld.world.applyPhysicsForBody(body, testWorld.levelGeometry, 0.1);
	
	EXPECT_EQ(body.bounds.origin, targetPt);
}
