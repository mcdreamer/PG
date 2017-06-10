#include "PG/core/Rect.h"

#include <iostream>

namespace PG {

//--------------------------------------------------------
bool operator==(const PGRect& r1, const PGRect& r2)
{
    return r1.origin == r2.origin && r1.size == r2.size;
}

//--------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const PGRect& r)
{
    os << r.origin << ": " << r.size;

    return os;
}

}
