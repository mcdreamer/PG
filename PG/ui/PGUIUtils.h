#pragma once

#include "PG/core/Point.h"
#include "PG/graphics/Node.h"

namespace PG {
namespace PGUIUtils {

PGPoint calculateNodeRelativePoint(const PGPoint& parentRelPt, const NodeHandle& node);

} // namespace PGUIUtils
}
