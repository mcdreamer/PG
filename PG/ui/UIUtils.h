#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/BindableValue.h"
#include "PG/core/Point.h"

namespace PG {

struct SceneHandle;

namespace UIUtils {

Point calculateNodeRelativePoint(const Point& parentRelPt, const NodeHandle& node);

void bindTextNodeToValue(NodeHandle& nodeHandle, BindableValue<std::string>& value);

//--------------------------------------------------------
template <typename T>
void bindTextNodeToValue(NodeHandle& nodeHandle, BindableValue<T>& value)
{
	value.setBinding([&](const T& newVal) { nodeHandle.node->setText(std::to_string(newVal)); });
}

NodeHandle createTextNode(const Point& pos, const Colour& colour, const int fontSize, SceneHandle& scene);

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const Point& pos,
							const Colour& colour,
							const int fontSize,
							NodeHandle& node,
							SceneHandle& scene,
							BindableValue<T>& value)
{
	node = createTextNode(pos, colour, fontSize, scene);
	
	bindTextNodeToValue(node, value);
}

}
}
