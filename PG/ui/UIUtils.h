#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/BindableValue.h"
#include "PG/core/Point.h"
#include "PG/core/Alignment.h"

namespace PG {

struct SceneHandle;
struct StyleSheet;

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
						  const PG::StyleSheet& styleSheet,
						  SceneHandle& scene);

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const Point& pos,
							const Colour& colour,
							const int fontSize,
							const Alignment alignment,
							const PG::StyleSheet& styleSheet,
							NodeHandle& node,
							SceneHandle& scene,
							BindableValue<T>& value)
{
	node = createTextNode(pos, colour, fontSize, alignment, styleSheet, scene);
	
	bindTextNodeToValue(node, value);
}

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const Point& pos,
							const Colour& colour,
							const int fontSize,
							const PG::StyleSheet& styleSheet,
							NodeHandle& node,
							SceneHandle& scene,
							BindableValue<T>& value)
{
	createTextNodeForValue(pos,
						   colour,
						   fontSize,
						   Alignment::kCentre,
						   styleSheet,
						   node,
						   scene,
						   value);
}

}
}
