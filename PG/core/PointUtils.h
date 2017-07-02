#pragma once

namespace PG {

class PGPoint;
class PGSize;

namespace PointUtils {

PGPoint scalePoint(PGPoint pt, float scale);
PGPoint multiplyPoints(PGPoint pt1, PGPoint pt2);
PGPoint addPoints(PGPoint pt1, PGPoint pt2);
PGPoint addToPoint(PGPoint pt, PGSize sz);
PGPoint subtractPoints(PGPoint pt1, PGPoint pt2);

}
}
