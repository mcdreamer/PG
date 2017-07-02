#pragma once

#include <vector>

namespace PG {

//--------------------------------------------------------
struct TileCoord
{
	TileCoord()
	: x(0), y(0)
	{}

    TileCoord(int x_, int y_)
    : x(x_), y(y_)
    {}

    int x;
    int y;
};

using TileCoordArray = std::vector<TileCoord>;

bool operator==(const TileCoord& c1, const TileCoord& c2);
bool operator!=(const TileCoord& c1, const TileCoord& c2);

}
