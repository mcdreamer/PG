#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/BindableValue.h"

namespace PG {

struct SceneHandle;

namespace UIUtils {

//--------------------------------------------------------
template <typename T>
void bindTextNodeToValue(NodeHandle& nodeHandle, BindableValue<T>& value)
{
	value.setBinding([&](const T& newVal) { nodeHandle.node->setText(std::to_string(newVal)); });
}

NodeHandle createTextNode(const PGPoint& pos, const Colour& colour, const int fontSize, SceneHandle& scene);

//--------------------------------------------------------
template <typename T>
void createTextNodeForValue(const PGPoint& pos,
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
