#include "PG/ui/UIElement.h"
#include "PG/ui/UIUtils.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/core/Rect.h"
#include "PG/core/RectUtils.h"

namespace PG {

//--------------------------------------------------------
void UIElement::show(NodeHandle parent, const Size& parentSize, const StyleSheet& styleSheet)
{
    auto root = NodeCreator::createNode();
    
    m_Root = parent.node->addChild(root);
    
    initUIElement(parentSize, styleSheet);
}

//--------------------------------------------------------
void UIElement::close()
{
    m_Root.node->removeFromParent();
}

//--------------------------------------------------------
void UIElement::addChild(UIElement* element, const Size& parentSize, const StyleSheet& styleSheet)
{
    element->show(m_Root, parentSize, styleSheet);
    
    m_Children.emplace_back(element);
}

//--------------------------------------------------------
void UIElement::addChild(std::unique_ptr<UIElement>& element, const Size& parentSize, const StyleSheet& styleSheet)
{
    element->show(m_Root, parentSize, styleSheet);
    
    m_Children.emplace_back(element.release());
}

//--------------------------------------------------------
Rect UIElement::getElementRect() const
{
    Rect combinedChildNodeRect;
    for (const auto* childNode : m_Root.node->getChildren())
    {
        combinedChildNodeRect = RectUtils::combineRects(combinedChildNodeRect, childNode->getRect());
    }

    combinedChildNodeRect = Rect(Point(0, 0), combinedChildNodeRect.size);

    return combinedChildNodeRect;
}

//--------------------------------------------------------
bool UIElement::handleClick(const Point& parentRelPt, UIMessageQueuePoster& msgPoster)
{
    auto elementLocalPt = UIUtils::calculateNodeRelativePoint(parentRelPt, m_Root);
    
    const auto elementRect = getElementRect();
    const bool elementRootIsInvisible = RectUtils::isEmpty(elementRect.size);

    if (elementRootIsInvisible || RectUtils::containsPoint(elementRect, elementLocalPt))
    {
        for (auto& childElement : m_Children)
        {
            if (childElement->handleClick(elementLocalPt, msgPoster))
            {
                return true;
            }
        }
        
        if (!elementRootIsInvisible)
        {
            clicked(msgPoster);

            return true;
        }
    }
    
    return false;
}

}
