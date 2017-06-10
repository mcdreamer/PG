#include "PG/app/GameConstants.h"

namespace PG {

namespace Internal {

int g_TileSize = 2;

}

int GameConstants::tileSize() { return Internal::g_TileSize; }

}
