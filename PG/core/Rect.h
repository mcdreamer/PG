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
    
    Point origin;
    Size  size;
    
    double left() const { return origin.x - (size.width / 2.0); }
    double right() const { return origin.x + (size.width / 2.0); }
    double top() const { return origin.y - (size.height / 2.0); }
    double bottom() const { return origin.y + (size.height / 2.0); }
};

bool operator==(const Rect& r1, const Rect& r2);
std::ostream& operator<<(std::ostream& os, const Rect& r);

}
