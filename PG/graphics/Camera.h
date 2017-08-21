#pragma once

#include "PG/core/Size.h"
#include "PG/core/Rect.h"

namespace PG {

class Point;
	
//--------------------------------------------------------
class Camera
{
public:
	Camera(const Size& viewSize, const Rect& staticZone)
	: m_ViewSize(viewSize),
	m_StaticZone(staticZone)
	{}
	
	Point calculateCameraPoint(const Point& currentCameraPt,
							   const Point& controllingPt) const;
	
private:
	Size	m_ViewSize;
	Rect	m_StaticZone;
};

}
