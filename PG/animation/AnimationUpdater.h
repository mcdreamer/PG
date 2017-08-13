#pragma once

namespace PG {

class AnimationPtrArray;

//--------------------------------------------------------
class AnimationUpdater
{
public:
	void updateAnimations(AnimationPtrArray& animations, double dt) const;
	
	void removeCompletedAnimations(AnimationPtrArray& animations) const;
};

}
