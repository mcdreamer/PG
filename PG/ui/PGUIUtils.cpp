#include "PG/ui/PGUIUtils.h"
#include "PG/core/Rect.h"
#include "PG/core/PGRectUtils.h"

namespace PG {
namespace PGUIUtils {

//--------------------------------------------------------
PGPoint calculateNodeRelativePoint(const PGPoint& parentRelPt, const NodeHandle& node)
{
    auto nodePos = node.node->getPosition();
    
    return PGPoint(parentRelPt.x - nodePos.x, parentRelPt.y - nodePos.y);
}

} // namespace PGUIUtils
}
