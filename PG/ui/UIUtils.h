#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/BindableValue.h"
#include "PG/core/Point.h"
#include "PG/core/Alignment.h"

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

NodeHandle createTextNode(const Point& pos,
						  const Colour& colour,
						  const int fontSize,
						  const Alignment alignment,
						  SceneHandle& scene);

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const Point& pos,
							const Colour& colour,
							const int fontSize,
							const Alignment alignment,
							NodeHandle& node,
							SceneHandle& scene,
							BindableValue<T>& value)
{
	node = createTextNode(pos, colour, fontSize, alignment, scene);
	
	bindTextNodeToValue(node, value);
}

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const Point& pos,
							const Colour& colour,
							const int fontSize,
							NodeHandle& node,
							SceneHandle& scene,
							BindableValue<T>& value)
{
	createTextNodeForValue(pos,
						   colour,
						   fontSize,
						   Alignment::kCentre,
						   node,
						   scene,
						   value);
}

}
}
