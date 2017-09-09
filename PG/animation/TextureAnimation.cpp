#include "PG/animation/TextureAnimation.h"

namespace PG {

//--------------------------------------------------------
TextureAnimation::TextureAnimation(const TextureAnimationDefinition& animationDef,
								   const NodeHandle& node)
: m_AnimationDef(animationDef),
m_Node(node),
m_Time(0.0),
m_FramesPerRow((int)(node.node->getSize().width / animationDef.getFrameSize().width))
{
	m_Node.node->setTextureRect(getRectForFrame(0));
}

//--------------------------------------------------------
void TextureAnimation::update(double dt)
{
	m_Time += dt;
	
	m_Node.node->setTextureRect(getRectForFrame((int)(m_Time / m_AnimationDef.getFrameDuration())));
}

//--------------------------------------------------------
bool TextureAnimation::isComplete()
{
	return false;
}

//--------------------------------------------------------
Rect TextureAnimation::getRectForFrame(const int frame) const
{
	const auto& sz = m_AnimationDef.getFrameSize();
	
	const int thisFrame = frame % m_AnimationDef.getFrameCount();
	
	Point frameCentrePt;
	frameCentrePt.x = (sz.width * (thisFrame % m_FramesPerRow)) + sz.width / 2.0;
	frameCentrePt.y = ((thisFrame / m_FramesPerRow) * sz.height) + (sz.height / 2.0);
	
	return Rect(frameCentrePt, sz);
}

}
