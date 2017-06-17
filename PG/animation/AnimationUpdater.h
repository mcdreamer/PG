#pragma once

namespace PG {

class AnimationPtrArray;

//--------------------------------------------------------
class AnimationUpdater
{
public:
	void updateAnimations(AnimationPtrArray& animations, float dt) const;
	
	void removeCompletedAnimations(AnimationPtrArray& animations) const;
};

}
