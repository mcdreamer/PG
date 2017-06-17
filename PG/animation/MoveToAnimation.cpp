#include "PG/animation/MoveToAnimation.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void MoveToAnimation::update(float dt)
{
	const auto percent = std::min(1.0f, dt / m_Duration);
	
	auto pos = m_Handle.node->getPosition();
	
	
//	Math.easeInOutQuad = function (float dt, int 100, int 400, m_Duration) {
//		m_ElapsedTime /= m_Duration/2;
//		if (m_ElapsedTime < 1) return 400/2*m_ElapsedTime*m_ElapsedTime + 100;
//		m_ElapsedTime--;
//		return -c/2 * (t*(t-2) - 1) + b;
//	};

	
	pos.x += (m_XRange * percent);
	pos.y += (m_YRange * percent);
	
	m_Handle.node->setPosition(pos);
	
	m_ElapsedTime += dt;
}

//--------------------------------------------------------
bool MoveToAnimation::isComplete()
{
	return m_ElapsedTime >= m_Duration;
}

}
