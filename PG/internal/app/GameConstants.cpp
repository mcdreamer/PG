#include "PG/app/GameConstants.h"

namespace PG {

namespace Internal {

int tileSize = 2;

}

int GameConstants::tileSize() { return Internal::tileSize; }

}
