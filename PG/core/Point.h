#pragma once

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class Point
{
public:
    Point()
    : x(0), y(0)
    {}

    Point(double x_, double y_)
    : x(x_), y(y_)
    {}
    
    double x;
    double y;
};

bool operator==(const Point& p1, const Point& p2);
bool operator!=(const Point& p1, const Point& p2);
std::ostream& operator<<(std::ostream& os, const Point& p);

}
