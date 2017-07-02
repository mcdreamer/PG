#pragma once

#include "Rect.h"
#include "Point.h"

namespace PG {

//--------------------------------------------------------
namespace PGRectUtils
{
    PGRect  getIntersection(const PGRect& rectOne, const PGRect& rectTwo);
    bool    isEmpty(const PGRect& r);
    bool    isEmpty(const PGSize& s);
    bool    containsPoint(const PGRect& r, const PGPoint& pt);
    PGRect  combineRects(const PGRect& r1, const PGRect& r2);
    
}

}
