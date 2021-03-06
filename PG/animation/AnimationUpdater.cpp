#include "PG/animation/AnimationUpdater.h"
#include "PG/animation/IAnimation.h"

#include <algorithm>

namespace PG {

//--------------------------------------------------------
void AnimationUpdater::updateAnimations(AnimationPtrArray& animations, double dt) const
{
	for (auto& animation : animations)
	{
		animation->update(dt);
	}
}

//--------------------------------------------------------
void AnimationUpdater::removeCompletedAnimations(AnimationPtrArray& animations) const
{
	animations.erase(std::remove_if(animations.begin(), animations.end(), [](const auto& a) { return a->isComplete(); }), animations.end());
}

}
