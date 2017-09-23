#include "PG/core/PointUtils.h"
#include "PG/core/Point.h"
#include "PG/core/Size.h"

namespace PG {
namespace PointUtils {

//--------------------------------------------------------
Point scalePoint(Point pt, float scale)
{
	return Point(pt.x * scale, pt.y * scale);
}

//--------------------------------------------------------
Point multiplyPoints(Point pt1, Point pt2)
{
	return Point(pt1.x * pt2.x, pt1.y * pt2.y);
}

//--------------------------------------------------------
Point addPoints(Point pt1, Point pt2)
{
	return Point(pt1.x + pt2.x, pt1.y + pt2.y);
}

//--------------------------------------------------------
Point addToPoint(Point pt, Size sz)
{
	return Point(pt.x + sz.width, pt.y + sz.height);
}

//--------------------------------------------------------
Point subtractPoints(Point pt1, Point pt2)
{
	return Point(pt1.x - pt2.x, pt1.y - pt2.y);
}

//--------------------------------------------------------
Point swapValues(Point pt)
{
	return Point(pt.y, pt.x);
}

}
}
