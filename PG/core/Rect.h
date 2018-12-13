#pragma once

#include "PG/core/Point.h"
#include "PG/core/Size.h"

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class Rect
{
public:
    Rect()
    {}

    Rect(Point pt, Size sz)
    : origin(pt), size(sz)
    {}
	
	Rect(Point topLeft, Point bottomRight)
	: size(bottomRight.x - topLeft.x, bottomRight.y - topLeft.y)
	{
		origin.x = topLeft.x + (size.width / 2.0);
		origin.y = topLeft.y + (size.height / 2.0);
	}
	
    Point origin;
    Size  size;
    
    double left() const { return origin.x - (size.width / 2.0); }
    double right() const { return origin.x + (size.width / 2.0); }
    double top() const { return origin.y - (size.height / 2.0); }
    double bottom() const { return origin.y + (size.height / 2.0); }
	
	Point topLeft() const { return Point(left(), top()); }
	Point bottomRight() const { return Point(right(), bottom()); }
};

bool operator==(const Rect& r1, const Rect& r2);
std::ostream& operator<<(std::ostream& os, const Rect& r);

}
