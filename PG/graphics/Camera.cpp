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
Point Camera::calculateCameraPoint(const Point& currentCameraPt,
						   const Point& controllingPt) const
{
	const auto xToSet = getValueToSetOnAxis(currentCameraPt.x,
											controllingPt.x,
											m_ViewSize.width,
											m_StaticZone.left(),
											m_StaticZone.right());
	
	const auto yToSet = getValueToSetOnAxis(currentCameraPt.y,
											controllingPt.y,
											m_ViewSize.height,
											m_StaticZone.top(),
											m_StaticZone.bottom());
	
	return Point(xToSet, yToSet);
}

}
