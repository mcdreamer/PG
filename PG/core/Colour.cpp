#include "PG/core/Colour.h"

namespace PG {

Colour Colour::white() { return Colour(255, 255, 255); }
Colour Colour::black() { return Colour(0, 0, 0); }
Colour Colour::red() { return Colour(255, 0, 0); }
Colour Colour::green() { return Colour(0, 255, 0); }
Colour Colour::blue() { return Colour(0, 0, 255); }

}
