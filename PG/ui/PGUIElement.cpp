#include "PG/ui/PGUIElement.h"
#include "PG/ui/PGUIUtils.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/NodeCreator.h"
#include "PG/core/Rect.h"
#include "PG/core/PGRectUtils.h"

namespace PG {

//--------------------------------------------------------
void PGUIElement::show(IScene& scene, const StyleSheet& styleSheet)
{
    auto root = NodeCreator::createNode();
    m_Root = scene.addChild(root);
    
    initUIElement(styleSheet);
}

//--------------------------------------------------------
void PGUIElement::show(NodeHandle parent, const StyleSheet& styleSheet)
{
    auto root = NodeCreator::createNode();
    
    m_Root = parent.node->addChild(root);
    
    initUIElement(styleSheet);
}

//--------------------------------------------------------
void PGUIElement::close()
{
    m_Root.node->removeFromParent();
}

//--------------------------------------------------------
void PGUIElement::addChild(PGUIElement* element, const StyleSheet& styleSheet)
{
    element->show(m_Root, styleSheet);
    
    m_Children.emplace_back(element);
}

//--------------------------------------------------------
void PGUIElement::addChild(std::unique_ptr<PGUIElement>& element, const StyleSheet& styleSheet)
{
    element->show(m_Root, styleSheet);
    
    m_Children.emplace_back(element.release());
}

//--------------------------------------------------------
PGRect PGUIElement::getElementRect() const
{
    PGRect combinedChildNodeRect;
    for (const auto* childNode : m_Root.node->getChildren())
    {
        combinedChildNodeRect = PGRectUtils::combineRects(combinedChildNodeRect, childNode->getRect());
    }

    combinedChildNodeRect = PGRect(PGPoint(0, 0), combinedChildNodeRect.size);

    return combinedChildNodeRect;
}

//--------------------------------------------------------
bool PGUIElement::handleClick(const PGPoint& parentRelPt, PGUIMessageQueuePoster& msgPoster)
{
    auto elementLocalPt = PGUIUtils::calculateNodeRelativePoint(parentRelPt, m_Root);
    
    const auto elementRect = getElementRect();
    const bool elementRootIsInvisible = PGRectUtils::isEmpty(elementRect.size);

    if (elementRootIsInvisible || PGRectUtils::containsPoint(elementRect, elementLocalPt))
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
