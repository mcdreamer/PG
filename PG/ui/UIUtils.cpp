#include "PG/ui/UIUtils.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/core/Rect.h"
#include "PG/core/RectUtils.h"

namespace PG {
namespace UIUtils {

//--------------------------------------------------------
Point calculateNodeRelativePoint(const Point& parentRelPt, const NodeHandle& node)
{
	auto nodePos = node.node->getPosition();

	return Point(parentRelPt.x - nodePos.x, parentRelPt.y - nodePos.y);
}

//--------------------------------------------------------
NodeHandle createTextNode(const Point& pos, const Colour& colour, const int fontSize, SceneHandle& scene)
{
	auto textNode = NodeCreator::createTextNode(scene.scene->getStyleSheet().uiFontName, fontSize);
	textNode->setPosition(pos);
	textNode->setColour(colour);
	return scene.scene->addChild(textNode);
}

}
}
