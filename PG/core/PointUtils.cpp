#include "PointUtils.h"

namespace PG {

//--------------------------------------------------------
PGPoint PGPointScale(PGPoint pt, float scale)
{
	return PGPoint(pt.x * scale, pt.y * scale);
}

//--------------------------------------------------------
PGPoint PGPointMultiply(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x * pt2.x, pt1.y * pt2.y);
}

//--------------------------------------------------------
PGPoint PGPointAdd(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x + pt2.x, pt1.y + pt2.y);
}

//--------------------------------------------------------
PGPoint PGPointSubtract(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x - pt2.x, pt1.y - pt2.y);
}

}
