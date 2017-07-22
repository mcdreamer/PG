#pragma once

#include "PG/core/Size.h"

#include <vector>

namespace PG {

class PGPoint;

//--------------------------------------------------------
class UIPositionCalculator
{
public:
	UIPositionCalculator(const PGSize& size);
	
	PGPoint fromTopLeftCorner(const PGSize& distance) const;
	PGPoint fromTopRightCorner(const PGSize& distance) const;
	PGPoint fromBottomLeftCorner(const PGSize& distance) const;
	PGPoint fromBottomRightCorner(const PGSize& distance) const;
	
	PGPoint fromLeftMid(const PGSize& distance) const;
	PGPoint fromRightMid(const PGSize& distance) const;
	PGPoint fromTopMid(const PGSize& distance) const;
	PGPoint fromBottomMid(const PGSize& distance) const;
	
	PGPoint atCentre() const;

	std::vector<PGPoint> multipleLeftToRight(const PGPoint& startPos, const int count, const double padding) const;
	std::vector<PGPoint> multipleTopToBottom(const PGPoint& startPos, const int count, const double padding) const;

	std::vector<PGPoint> multipleAcrossCentre(const double startX, const int count, const double padding) const;
	std::vector<PGPoint> multipleDownCentre(const double startY, const int count, const double padding) const;
	
	std::vector<PGPoint> multiplePositions(const PGPoint& startPos, const PGPoint& endPos, const int count) const;
	
private:
	const PGSize m_Size;
};

}
