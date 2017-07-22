#pragma once

#include "PG/core/Rect.h"
#include "PG/core/Point.h"

namespace PG {

//--------------------------------------------------------
namespace RectUtils
{
    Rect  getIntersection(const Rect& rectOne, const Rect& rectTwo);
    bool    isEmpty(const Rect& r);
    bool    isEmpty(const Size& s);
    bool    containsPoint(const Rect& r, const Point& pt);
    Rect  combineRects(const Rect& r1, const Rect& r2);
    
}

}
