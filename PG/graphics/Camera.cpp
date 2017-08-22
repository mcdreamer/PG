#include "PG/graphics/Camera.h"
#include "PG/core/Point.h"

namespace PG {

namespace
{
	//--------------------------------------------------------
	double getValueToSetOnAxis(const double current,
							   const double controlling,
							   const double viewSizeOnAxis,
							   const double lowThreshold,
							   const double highThreshold)
	{
		{
			auto newPos = -controlling + (viewSizeOnAxis / 2.0) + lowThreshold;
			if (newPos > current)
			{
				return newPos;
			}
		}
		{
			auto newPos = -controlling + (viewSizeOnAxis / 2.0) + highThreshold;
			if (newPos < current)
			{
				return newPos;
			}
		}
		
		return current;
	}
}
	
//--------------------------------------------------------
Point Camera::calculateCameraPoint(const Size& viewSize,
								   const Point& currentCameraPt) const
{
	if (!m_ControllingNode.node)
	{
		return currentCameraPt;
	}

	const auto controllingPt = m_ControllingNode.node->getPosition();

	const Rect staticRect(Point(0, 0),
						  Size(m_StaticZone.width * viewSize.width, m_StaticZone.height * viewSize.height));

	const auto xToSet = getValueToSetOnAxis(currentCameraPt.x,
											controllingPt.x,
											viewSize.width,
											staticRect.left(),
											staticRect.right());
	
	const auto yToSet = getValueToSetOnAxis(currentCameraPt.y,
											controllingPt.y,
											viewSize.height,
											staticRect.top(),
											staticRect.bottom());
	
	return Point(xToSet, yToSet);
}

}
