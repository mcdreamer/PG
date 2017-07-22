#pragma once

#include "PG/core/Size.h"

#include <vector>

namespace PG {

class Point;

//--------------------------------------------------------
class UIPositionCalculator
{
public:
	UIPositionCalculator(const Size& size);
	
	Point fromTopLeftCorner(const Size& distance) const;
	Point fromTopRightCorner(const Size& distance) const;
	Point fromBottomLeftCorner(const Size& distance) const;
	Point fromBottomRightCorner(const Size& distance) const;
	
	Point fromLeftMid(const Size& distance) const;
	Point fromRightMid(const Size& distance) const;
	Point fromTopMid(const Size& distance) const;
	Point fromBottomMid(const Size& distance) const;
	
	Point atCentre() const;

	std::vector<Point> multipleLeftToRight(const Point& startPos, const int count, const double padding) const;
	std::vector<Point> multipleTopToBottom(const Point& startPos, const int count, const double padding) const;

	std::vector<Point> multipleAcrossCentre(const double startX, const int count, const double padding) const;
	std::vector<Point> multipleDownCentre(const double startY, const int count, const double padding) const;
	
	std::vector<Point> multiplePositions(const Point& startPos, const Point& endPos, const int count) const;
	
private:
	const Size m_Size;
};

}
