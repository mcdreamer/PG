#include "PG/ui/UIPositionCalculator.h"
#include "PG/core/Point.h"

#include <vector>

namespace PG {

//--------------------------------------------------------
UIPositionCalculator::UIPositionCalculator(const PGSize& size)
: m_Size(size)
{}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromTopLeftCorner(const PGSize& distance) const
{
	return PGPoint(distance.width, distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromTopRightCorner(const PGSize& distance) const
{
	return PGPoint(m_Size.width - distance.width, distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromBottomLeftCorner(const PGSize& distance) const
{
	return PGPoint(distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromBottomRightCorner(const PGSize& distance) const
{
	return PGPoint(m_Size.width - distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromLeftMid(const PGSize& distance) const
{
	return PGPoint(distance.width, (m_Size.height / 2.0) + distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromRightMid(const PGSize& distance) const
{
	return PGPoint(m_Size.width - distance.width, (m_Size.height / 2.0) + distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromTopMid(const PGSize& distance) const
{
	return PGPoint((m_Size.width / 2.0) + distance.width, distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::fromBottomMid(const PGSize& distance) const
{
	return PGPoint((m_Size.width / 2.0) + distance.width, m_Size.height - distance.height);
}

//--------------------------------------------------------
PGPoint UIPositionCalculator::atCentre() const
{
	return PGPoint(m_Size.width / 2.0, m_Size.height / 2.0);
}

//--------------------------------------------------------
std::vector<PGPoint> UIPositionCalculator::multipleLeftToRight(const PGPoint& startPos, const int count, const double padding) const
{
	return multiplePositions(startPos,
							 PGPoint(startPos.x + (padding * (double)count), startPos.y),
							 count);
}

//--------------------------------------------------------
std::vector<PGPoint> UIPositionCalculator::multipleTopToBottom(const PGPoint& startPos, const int count, const double padding) const
{
	return multiplePositions(startPos,
							 PGPoint(startPos.x, startPos.y + (padding * (double)count)),
							 count);
}

//--------------------------------------------------------
std::vector<PGPoint> UIPositionCalculator::multipleAcrossCentre(const double startX, const int count, const double padding) const
{
	return multipleLeftToRight(PGPoint(startX, m_Size.height / 2.0), count, padding);
}

//--------------------------------------------------------
std::vector<PGPoint> UIPositionCalculator::multipleDownCentre(const double startY, const int count, const double padding) const
{
	return multipleTopToBottom(PGPoint(m_Size.width / 2.0, startY), count, padding);
}

//--------------------------------------------------------
std::vector<PGPoint> UIPositionCalculator::multiplePositions(const PGPoint& startPos, const PGPoint& endPos, const int count) const
{
	std::vector<PGPoint> pts;
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
