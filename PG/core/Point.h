#pragma once

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class PGPoint
{
public:
    PGPoint()
    : x(0), y(0)
    {}

    PGPoint(double x_, double y_)
    : x(x_), y(y_)
    {}
    
    double x;
    double y;
};

bool operator==(const PGPoint& p1, const PGPoint& p2);
bool operator!=(const PGPoint& p1, const PGPoint& p2);
std::ostream& operator<<(std::ostream& os, const PGPoint& p);

}
