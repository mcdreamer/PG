#include "PG/ui/UIUtils.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"

namespace PG {
namespace UIUtils {

//--------------------------------------------------------
NodeHandle createTextNode(const PGPoint& pos, const Colour& colour, const int fontSize, SceneHandle& scene)
{
	auto textNode = NodeCreator::createTextNode(scene.scene->getStyleSheet().uiFontName, fontSize);
	textNode->setPosition(pos);
	textNode->setColour(colour);
	return scene.scene->addChild(textNode);
}

}
}
