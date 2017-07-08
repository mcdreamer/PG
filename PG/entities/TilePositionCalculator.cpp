#include "PG/entities/TilePositionCalculator.h"
#include "PG/app/GameConstants.h"

namespace PG {

//--------------------------------------------------------
PGPoint TilePositionCalculator::calculatePoint(const TileCoord& c) const
{
    auto halfTileSize = PG::GameConstants::tileSize() / 2;
    return PGPoint((PG::GameConstants::tileSize() * c.x) + halfTileSize, (PG::GameConstants::tileSize() * c.y) + halfTileSize);
}

//--------------------------------------------------------
PGPoint TilePositionCalculator::calculatePoint(const int x, const int y) const
{
    return calculatePoint(TileCoord(x, y));
}

//--------------------------------------------------------
TileCoord TilePositionCalculator::calculateTileCoord(const PGPoint& pt) const
{
    return TileCoord { (int)pt.x / PG::GameConstants::tileSize(), (int)pt.y / PG::GameConstants::tileSize() };
}

}
