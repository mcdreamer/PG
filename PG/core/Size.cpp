#include "PG/core/Size.h"

#include <iostream>

namespace PG {

//--------------------------------------------------------
bool operator==(const PGSize& s1, const PGSize& s2)
{
    return s1.width == s2.width && s1.height == s2.height;
}

//--------------------------------------------------------
bool operator!=(const PGSize& s1, const PGSize& s2)
{
    return !operator==(s1, s2);
}

//--------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const PGSize& s)
{
    os << "(w = " << s.width << ", h = " << s.height << ")";
    return os;
}

}
