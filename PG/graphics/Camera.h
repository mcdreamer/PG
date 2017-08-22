#pragma once

#include "PG/core/Size.h"
#include "PG/core/Rect.h"
#include "PG/graphics/Node.h"

namespace PG {

class Point;
	
//--------------------------------------------------------
class Camera
{
public:
	Camera()
	{}
	
	Camera(const Size& staticZone,
		   const NodeHandle& controllingNode)
	: m_StaticZone(staticZone),
	m_ControllingNode(controllingNode)
	{}
	
	Point calculateCameraPoint(const Size& viewSize,
							   const Point& currentCameraPt) const;
	
private:
	Size		m_StaticZone;
	NodeHandle	m_ControllingNode;
};

}
