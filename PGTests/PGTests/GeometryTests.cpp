#include "GeometryTests.h"
#include "gtest/gtest.h"

#include "PG/core/PGRectUtils.h"
#include "PG/core/Rect.h"
#include "PG/core/Point.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/app/GameConstants.h"

using namespace PG;

//--------------------------------------------------------
TEST(GeometryTests,testTilePositionCalculator)
{
	TilePositionCalculator tpc;
	EXPECT_EQ(2, GameConstants::tileSize());
	
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(PGPoint(0, 0)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(PGPoint(0.5, 0.5)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(PGPoint(1, 1)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(PGPoint(1.5, 1.5)));
	EXPECT_EQ(TileCoord(1, 1), tpc.calculateTileCoord(PGPoint(2, 2)));
	
	EXPECT_EQ(PGPoint(1, 1), tpc.calculatePoint(TileCoord(0, 0)));
	EXPECT_EQ(PGPoint(3, 1), tpc.calculatePoint(TileCoord(1, 0)));
	EXPECT_EQ(PGPoint(1, 3), tpc.calculatePoint(TileCoord(0, 1)));
	EXPECT_EQ(PGPoint(3, 3), tpc.calculatePoint(TileCoord(1, 1)));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_ContainsPoint)
{
    const PGRect rect(PGPoint(100, 100), PGSize(50, 50));
    
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(100, 100)));
    
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(80, 100)));
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(100, 80)));
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(80, 80)));
    
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(100, 120)));
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(120, 100)));
    EXPECT_TRUE(PGRectUtils::containsPoint(rect, PGPoint(120, 120)));
    
    EXPECT_FALSE(PGRectUtils::containsPoint(rect, PGPoint(70, 70)));
    EXPECT_FALSE(PGRectUtils::containsPoint(rect, PGPoint(130, 130)));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_CombineRects)
{
    {
        const auto r = PGRectUtils::combineRects(PGRect(PGPoint(100, 100), PGSize(50, 50)),
                                                 PGRect(PGPoint(100, 100), PGSize(50, 50)));
        
        EXPECT_EQ(PGRect(PGPoint(100, 100), PGSize(50, 50)), r);
    }
    {
        const auto r = PGRectUtils::combineRects(PGRect(PGPoint(100, 100), PGSize(50, 100)),
                                                 PGRect(PGPoint(100, 100), PGSize(50, 50)));
        
        EXPECT_EQ(PGRect(PGPoint(100, 100), PGSize(50, 100)), r);
    }
    {
        const auto r = PGRectUtils::combineRects(PGRect(PGPoint(0, 0), PGSize(50, 50)),
                                                 PGRect(PGPoint(100, 100), PGSize(50, 50)));
        
        EXPECT_EQ(PGRect(PGPoint(50, 50), PGSize(150, 150)), r);
    }
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_isEmpty)
{
	EXPECT_TRUE(PGRectUtils::isEmpty(PGRect(PGPoint(100, 100), PGSize(0, 0))));
	EXPECT_TRUE(PGRectUtils::isEmpty(PGRect(PGPoint(100, 100), PGSize(10, 0))));
	EXPECT_TRUE(PGRectUtils::isEmpty(PGRect(PGPoint(100, 100), PGSize(0, 10))));
	EXPECT_FALSE(PGRectUtils::isEmpty(PGRect(PGPoint(100, 100), PGSize(10, 10))));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_getIntersection)
{
	const PGRect rect(PGPoint(100, 100), PGSize(50, 50));
	
	{
		const auto i = PGRectUtils::getIntersection(rect, PGRect(PGPoint(100, 49), PGSize(50, 50)));
		EXPECT_TRUE(PGRectUtils::isEmpty(i));
	}
	{
		const auto i = PGRectUtils::getIntersection(rect, PGRect(PGPoint(100, 50), PGSize(50, 50)));
		EXPECT_TRUE(PGRectUtils::isEmpty(i));
	}
}
