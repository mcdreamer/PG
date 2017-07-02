#include "PG/core/PointUtils.h"
#include "PG/core/Point.h"
#include "PG/core/Size.h"

namespace PG {
namespace PointUtils {

//--------------------------------------------------------
PGPoint scalePoint(PGPoint pt, float scale)
{
	return PGPoint(pt.x * scale, pt.y * scale);
}

//--------------------------------------------------------
PGPoint multiplyPoints(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x * pt2.x, pt1.y * pt2.y);
}

//--------------------------------------------------------
PGPoint addPoints(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x + pt2.x, pt1.y + pt2.y);
}

//--------------------------------------------------------
PGPoint addToPoint(PGPoint pt, PGSize sz)
{
	return PGPoint(pt.x + sz.width, pt.y + sz.height);
}

//--------------------------------------------------------
PGPoint subtractPoints(PGPoint pt1, PGPoint pt2)
{
	return PGPoint(pt1.x - pt2.x, pt1.y - pt2.y);
}

}
}
