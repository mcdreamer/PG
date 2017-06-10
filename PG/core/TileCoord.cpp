#include "PG/core/TileCoord.h"

namespace PG {

//--------------------------------------------------------
bool operator==(const TileCoord& c1, const TileCoord& c2)
{
    return c1.x == c2.x && c1.y == c2.y;
}

//--------------------------------------------------------
bool operator!=(const TileCoord& c1, const TileCoord& c2)
{
    return !operator==(c1, c2);
}

}
