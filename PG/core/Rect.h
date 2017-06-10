#pragma once

#include "PG/core/Point.h"
#include "PG/core/Size.h"

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class PGRect
{
public:
    PGRect()
    {}

    PGRect(PGPoint pt, PGSize sz)
    : origin(pt), size(sz)
    {}
    
    PGPoint origin;
    PGSize  size;
    
    double left() const { return origin.x - (size.width / 2.0); }
    double right() const { return origin.x + (size.width / 2.0); }
    double top() const { return origin.y - (size.height / 2.0); }
    double bottom() const { return origin.y + (size.height / 2.0); }
};

bool operator==(const PGRect& r1, const PGRect& r2);
std::ostream& operator<<(std::ostream& os, const PGRect& r);

}
