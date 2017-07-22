#include "PG/ui/UIPositionCalculator.h"
#include "PG/core/Point.h"

namespace PG {

//--------------------------------------------------------
UIPositionCalculator::UIPositionCalculator(const Size& size)
: m_Size(size)
{}

//--------------------------------------------------------
Point UIPositionCalculator::fromTopLeftCorner(const Size& distance) const
{
	return Point(distance.width, distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromTopRightCorner(const Size& distance) const
{
	return Point(m_Size.width - distance.width, distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromBottomLeftCorner(const Size& distance) const
{
	return Point(distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromBottomRightCorner(const Size& distance) const
{
	return Point(m_Size.width - distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromLeftMid(const Size& distance) const
{
	return Point(distance.width, (m_Size.height / 2.0) + distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromRightMid(const Size& distance) const
{
	return Point(m_Size.width - distance.width, (m_Size.height / 2.0) + distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromTopMid(const Size& distance) const
{
	return Point((m_Size.width / 2.0) + distance.width, distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::fromBottomMid(const Size& distance) const
{
	return Point((m_Size.width / 2.0) + distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
Point UIPositionCalculator::atCentre() const
{
	return Point(m_Size.width / 2.0, m_Size.height / 2.0);
}

//--------------------------------------------------------
std::vector<Point> UIPositionCalculator::multipleLeftToRight(const Point& startPos, const int count, const double padding) const
{
	return multiplePositions(startPos,
							 Point(startPos.x + (padding * (double)count), startPos.y),
							 count);
}

//--------------------------------------------------------
std::vector<Point> UIPositionCalculator::multipleTopToBottom(const Point& startPos, const int count, const double padding) const
{
	return multiplePositions(startPos,
							 Point(startPos.x, startPos.y + (padding * (double)count)),
							 count);
}

//--------------------------------------------------------
std::vector<Point> UIPositionCalculator::multipleAcrossCentre(const double startX, const int count, const double padding) const
{
	return multipleLeftToRight(Point(startX, m_Size.height / 2.0), count, padding);
}

//--------------------------------------------------------
std::vector<Point> UIPositionCalculator::multipleDownCentre(const double startY, const int count, const double padding) const
{
	return multipleTopToBottom(Point(m_Size.width / 2.0, startY), count, padding);
}

//--------------------------------------------------------
std::vector<Point> UIPositionCalculator::multiplePositions(const Point& startPos, const Point& endPos, const int count) const
{
	std::vector<Point> pts;
	pts.reserve((size_t)count);
	
	const double xDiff = (endPos.x - startPos.x) / (double)count;
	const double yDiff = (endPos.y - startPos.y) / (double)count;
	
	for (int pt = 0; pt < count; ++pt)
	{
		pts.emplace_back(startPos.x + (xDiff * (double)pt), startPos.y + (yDiff * (double)pt));
	}
	
	return pts;
}

}
