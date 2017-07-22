#pragma once

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class Size
{
public:
    Size()
    : width(0), height(0)
    {}
    
    Size(double width_, double height_)
    : width(width_), height(height_)
    {}
    
    double width;
    double height;
};

bool operator==(const Size& s1, const Size& s2);
bool operator!=(const Size& s1, const Size& s2);
std::ostream& operator<<(std::ostream& os, const Size& s);

}
