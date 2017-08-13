#include "PG/animation/MoveToAnimation.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void MoveToAnimation::update(double dt)
{
	const auto m_XRange = (m_EndPt.x - m_StartPt.x);
	const auto m_YRange = (m_EndPt.y - m_StartPt.y);

	m_ElapsedTime += dt;
	const auto percent = std::min(m_ElapsedTime / m_Duration, 1.0);

	const auto posx = m_StartPt.x + (m_XRange * percent);
	const auto posy = m_StartPt.y + (m_YRange * percent);
	
	m_Handle.node->setPosition(Point(posx, posy));
}

//--------------------------------------------------------
bool MoveToAnimation::isComplete()
{
	return m_ElapsedTime >= m_Duration;
}

}
