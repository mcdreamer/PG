#include "GeometryTests.h"
#include "gtest/gtest.h"

#include "PG/core/RectUtils.h"
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
	
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(Point(0, 0)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(Point(0.5, 0.5)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(Point(1, 1)));
	EXPECT_EQ(TileCoord(0, 0), tpc.calculateTileCoord(Point(1.5, 1.5)));
	EXPECT_EQ(TileCoord(1, 1), tpc.calculateTileCoord(Point(2, 2)));
	
	EXPECT_EQ(Point(1, 1), tpc.calculatePoint(TileCoord(0, 0)));
	EXPECT_EQ(Point(3, 1), tpc.calculatePoint(TileCoord(1, 0)));
	EXPECT_EQ(Point(1, 3), tpc.calculatePoint(TileCoord(0, 1)));
	EXPECT_EQ(Point(3, 3), tpc.calculatePoint(TileCoord(1, 1)));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_ContainsPoint)
{
    const Rect rect(Point(100, 100), Size(50, 50));
    
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(100, 100)));
    
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(80, 100)));
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(100, 80)));
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(80, 80)));
    
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(100, 120)));
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(120, 100)));
    EXPECT_TRUE(RectUtils::containsPoint(rect, Point(120, 120)));
    
    EXPECT_FALSE(RectUtils::containsPoint(rect, Point(70, 70)));
    EXPECT_FALSE(RectUtils::containsPoint(rect, Point(130, 130)));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_CombineRects)
{
    {
        const auto r = RectUtils::combineRects(Rect(Point(100, 100), Size(50, 50)),
                                                 Rect(Point(100, 100), Size(50, 50)));
        
        EXPECT_EQ(Rect(Point(100, 100), Size(50, 50)), r);
    }
    {
        const auto r = RectUtils::combineRects(Rect(Point(100, 100), Size(50, 100)),
                                                 Rect(Point(100, 100), Size(50, 50)));
        
        EXPECT_EQ(Rect(Point(100, 100), Size(50, 100)), r);
    }
    {
        const auto r = RectUtils::combineRects(Rect(Point(0, 0), Size(50, 50)),
                                                 Rect(Point(100, 100), Size(50, 50)));
        
        EXPECT_EQ(Rect(Point(50, 50), Size(150, 150)), r);
    }
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_isEmpty)
{
	EXPECT_TRUE(RectUtils::isEmpty(Rect(Point(100, 100), Size(0, 0))));
	EXPECT_TRUE(RectUtils::isEmpty(Rect(Point(100, 100), Size(10, 0))));
	EXPECT_TRUE(RectUtils::isEmpty(Rect(Point(100, 100), Size(0, 10))));
	EXPECT_FALSE(RectUtils::isEmpty(Rect(Point(100, 100), Size(10, 10))));
}

//--------------------------------------------------------
TEST(GeometryTests,testPGRectUtils_getIntersection)
{
	const Rect rect(Point(100, 100), Size(50, 50));
	
	{
		const auto i = RectUtils::getIntersection(rect, Rect(Point(100, 49), Size(50, 50)));
		EXPECT_TRUE(RectUtils::isEmpty(i));
	}
	{
		const auto i = RectUtils::getIntersection(rect, Rect(Point(100, 50), Size(50, 50)));
		EXPECT_TRUE(RectUtils::isEmpty(i));
	}
}
