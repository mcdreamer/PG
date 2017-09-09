#pragma once

#include "PG/core/Size.h"

namespace PG {

//--------------------------------------------------------
class TextureAnimationDefinition
{
public:
	TextureAnimationDefinition(const double frameDuration, const int frameCount, const Size& frameSize)
	: m_FrameDuration(frameDuration),
	m_FrameSize(frameSize),
	m_FrameCount(frameCount)
	{}
	
	double		getFrameDuration() const { return m_FrameDuration; }
	int			getFrameCount() const { return m_FrameCount; }
	const Size	getFrameSize() const { return m_FrameSize; }
	
private:
	double		m_FrameDuration;
	int			m_FrameCount;
	Size		m_FrameSize;
};

}
