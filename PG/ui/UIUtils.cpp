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
	auto nodePos = node.node->getRect().topLeft();

	return Point(parentRelPt.x - nodePos.x, parentRelPt.y - nodePos.y);
}

//--------------------------------------------------------
void bindTextNodeToValue(NodeHandle& nodeHandle, BindableValue<std::string>& value)
{
	value.setBinding([&](const auto& newVal) { nodeHandle.node->setText(newVal); });
}

//--------------------------------------------------------
NodeHandle createTextNode(const Point& pos,
						  const Colour& colour,
						  const int fontSize,
						  const Alignment alignment,
						  const PG::StyleSheet& styleSheet,
						  SceneHandle& scene)
{
	auto textNode = NodeCreator::createTextNode(styleSheet.uiFontName,
												fontSize,
												alignment);
	textNode->setPosition(pos);
	textNode->setColour(colour);
	return scene.scene->addChild(textNode);
}

}
}
