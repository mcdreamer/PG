#include "PG/core/Rect.h"

#include <iostream>

namespace PG {

//--------------------------------------------------------
bool operator==(const Rect& r1, const Rect& r2)
{
    return r1.origin == r2.origin && r1.size == r2.size;
}

//--------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << r.origin << ": " << r.size;

    return os;
}

}
