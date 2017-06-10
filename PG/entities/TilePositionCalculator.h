#pragma once

#include "PG/core/Point.h"
#include "PG/core/TileCoord.h"

namespace PG {

//--------------------------------------------------------
class TilePositionCalculator
{
public:
    PGPoint     calculatePoint(const TileCoord& c) const;
    PGPoint     calculatePoint(const int x, const int y) const;
    TileCoord   calculateTileCoord(const PGPoint& pt) const;
};

}
