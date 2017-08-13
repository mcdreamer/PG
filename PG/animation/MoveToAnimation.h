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
					const double duration)
	: m_Handle(handle),
	m_StartPt(handle.node->getPosition()),
	m_EndPt(destination),
	m_Duration(duration),
	m_ElapsedTime(0.0)
	{}

	virtual void update(double dt) override;
	virtual bool isComplete() override;
	
private:
	NodeHandle		m_Handle;
	Point			m_StartPt;
	Point			m_EndPt;
	const double	m_Duration;
	double			m_ElapsedTime;
};

}
