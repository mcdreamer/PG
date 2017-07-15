#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/BindableValue.h"

namespace PG {
namespace UIUtils {

//--------------------------------------------------------
template <typename T>
void bindTextNodeToValue(NodeHandle& nodeHandle, BindableValue<T>& value)
{
	value.setBinding([&](const T& newVal) { nodeHandle.node->setText(std::to_string(newVal)); });
}

}
}
