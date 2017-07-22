#pragma once

namespace PG {

class Point;
class Size;

namespace PointUtils {

Point scalePoint(Point pt, float scale);
Point multiplyPoints(Point pt1, Point pt2);
Point addPoints(Point pt1, Point pt2);
Point addToPoint(Point pt, Size sz);
Point subtractPoints(Point pt1, Point pt2);

}
}
