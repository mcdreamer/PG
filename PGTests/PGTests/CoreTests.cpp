#include "CoreTests.h"
#include "gtest/gtest.h"

#include "PG/core/BindableValue.h"
#include "PG/core/Rect.h"
#include "PG/core/RectUtils.h"

#include <string>

using namespace PG;

//--------------------------------------------------------
TEST(CoreTests,testBindableValue_int)
{
	BindableValue<int> v(10);
	
	v.set(11);

	int x = 0;
	
	v.setBinding([&](const auto& v) { x = v; });
	EXPECT_EQ(11, x);
	
	v.set(12);
	EXPECT_EQ(12, x);
	
	++v;
	EXPECT_EQ(13, x);
	
	--v;
	EXPECT_EQ(12, x);
	
	v = 123;
	EXPECT_EQ(123, x);
	
	EXPECT_EQ(123, *v);
}

//--------------------------------------------------------
TEST(CoreTests,testBindableValue_string)
{
	BindableValue<std::string> v("Test");
	
	std::string x;
	
	v.setBinding([&](const auto& v) { x = v; });
	EXPECT_EQ("Test", x);
	
	v.set("Hello");
	EXPECT_EQ("Hello", x);
}

//--------------------------------------------------------
TEST(CoreTests,testRectUtils)
{
	const Rect r1(Point(0, 0), Size(10, 10));
	const Rect r2(Point(5, 0), Size(10, 10));

	EXPECT_EQ(r1, RectUtils::getIntersection(r1, r1));
	EXPECT_EQ(Rect(Point(5, 0), Size(5, 10)), RectUtils::getIntersection(r1, r2));
}