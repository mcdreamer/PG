#pragma once

#include <iosfwd>

namespace PG {

//--------------------------------------------------------
class PGSize
{
public:
    PGSize()
    : width(0), height(0)
    {}
    
    PGSize(double width_, double height_)
    : width(width_), height(height_)
    {}
    
    double width;
    double height;
};

bool operator==(const PGSize& s1, const PGSize& s2);
bool operator!=(const PGSize& s1, const PGSize& s2);
std::ostream& operator<<(std::ostream& os, const PGSize& s);

}
