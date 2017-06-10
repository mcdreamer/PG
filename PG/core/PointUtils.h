#pragma once

#include "Point.h"

namespace PG {

PGPoint PGPointScale(PGPoint pt, float scale);
PGPoint PGPointMultiply(PGPoint pt1, PGPoint pt2);
PGPoint PGPointAdd(PGPoint pt1, PGPoint pt2);
PGPoint PGPointSubtract(PGPoint pt1, PGPoint pt2);

}
