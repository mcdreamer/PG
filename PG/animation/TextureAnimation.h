#pragma once

#include "PG/animation/IAnimation.h"
#include "PG/animation/TextureAnimationDefinition.h"
#include "PG/graphics/Node.h"

namespace PG {

class Rect;

//--------------------------------------------------------
class TextureAnimation : public IAnimation
{
public:
	TextureAnimation(const TextureAnimationDefinition& animationDef,
					 const NodeHandle& node);
	
	virtual void update(double dt) override;
	virtual bool isComplete() override;
	
private:
	TextureAnimationDefinition 	m_AnimationDef;
	NodeHandle					m_Node;
	int							m_FrameCount;
	double						m_Time;
	
	Rect getRectForFrame(const int frame) const;
};

}
