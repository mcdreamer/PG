#include "PG/core/Point.h"

#include <iostream>

namespace PG {

//--------------------------------------------------------
bool operator==(const PGPoint& p1, const PGPoint& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

//--------------------------------------------------------
bool operator!=(const PGPoint& p1, const PGPoint& p2)
{
    return !operator==(p1, p2);
}

//--------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const PGPoint& p)
{
    os << "(x = " << p.x << ", y = " << p.y << ")";
    
    return os;
}

}
