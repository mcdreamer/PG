#include "PG/animation/TextureAnimationUtils.h"
#include "PG/animation/TextureAnimation.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {
namespace TextureAnimationUtils {

//--------------------------------------------------------
NodeHandle createAndAddAnimatedTexture(const TextureAnimationDefinition& animationDef,
									   const std::string& imageName,
									   const Point& startPosition,
									   SceneHandle& m_Scene)
{
	auto node = PG::NodeCreator::createSpriteNode(imageName);
	node->setPosition(startPosition);
	auto nodeHandle = m_Scene.scene->addChild(node);
	
	AnimationPtr animation(new TextureAnimation(animationDef, nodeHandle));
	m_Scene.scene->addAnimation(animation);
	
	return nodeHandle;
}

}
}
