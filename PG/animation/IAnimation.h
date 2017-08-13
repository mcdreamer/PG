#pragma once

#include <memory>
#include <vector>

namespace PG {

//--------------------------------------------------------
class IAnimation
{
public:
	virtual ~IAnimation() {}

	virtual void update(double dt)=0;
	virtual bool isComplete()=0;
};

using AnimationPtr = std::unique_ptr<IAnimation>;
class AnimationPtrArray : public std::vector<AnimationPtr> {};

}
