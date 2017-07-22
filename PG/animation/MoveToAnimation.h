#pragma once

#include "PG/animation/IAnimation.h"
#include "PG/core/Point.h"
#include "PG/graphics/Node.h"

namespace PG {

class Point;

//--------------------------------------------------------
class MoveToAnimation : public IAnimation
{
public:
	MoveToAnimation(const NodeHandle& handle,
					const Point& destination,
					const float duration)
	: m_Handle(handle),
	m_XRange(destination.x - m_Handle.node->getPosition().x),
	m_YRange(destination.y - m_Handle.node->getPosition().y),
	m_Duration(duration),
	m_ElapsedTime(0.0)
	{}

	virtual void update(float dt) override;
	virtual bool isComplete() override;
	
private:
	NodeHandle		m_Handle;
	const double	m_XRange;
	const double	m_YRange;
	const float		m_Duration;
	float			m_ElapsedTime;
};

}
