#include "GeometryTests.h"
#include "gtest/gtest.h"

#include "PG/core/PGRectUtils.h"
#include "PG/core/Rect.h"
#include "PG/core/Point.h"

using namespace PG;

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
