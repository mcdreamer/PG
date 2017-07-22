#pragma once

#include "PG/core/Point.h"
#include "PG/core/TileCoord.h"

namespace PG {

//--------------------------------------------------------
class TilePositionCalculator
{
public:
    Point     calculatePoint(const TileCoord& c) const;
    Point     calculatePoint(const int x, const int y) const;
    TileCoord   calculateTileCoord(const Point& pt) const;
};

}
