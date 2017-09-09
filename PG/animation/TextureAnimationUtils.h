#pragma once

#include <string>

namespace PG {

struct NodeHandle;
struct SceneHandle;
class TextureAnimationDefinition;
class Point;

namespace TextureAnimationUtils {

NodeHandle createAndAddAnimatedTexture(const TextureAnimationDefinition& animationDef,
									   const std::string& imageName,
									   const Point& startPosition,
									   SceneHandle& scene);

}
}
