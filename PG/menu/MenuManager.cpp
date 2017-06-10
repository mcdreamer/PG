#include "PG/menu/MenuManager.h"
#include "PG/graphics/Scene.h"
#include "PG/graphics/Node.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

const char* kTag = "tag";

namespace
{
    //--------------------------------------------------------
    NodePtr createMenuTextNode(const MenuNode& menuNode)
    {
        auto n = NodeCreator::createTextNode("OpenSans-Regular", 40);
        n->setText(menuNode.getText());
        n->setColour(0, 255, 0, 1);
        n->addUserDataInt(kTag, menuNode.getTag());
        return n;
    }
}

//--------------------------------------------------------
void MenuManager::initAndDisplayMenu(INode& layer)
{
    m_Layer = &layer;
    
    enterMenu(m_TopLevelNode);
}

namespace
{
    //--------------------------------------------------------
    struct CurrentMenuNode
    {
        const MenuNodeList&                 nodes;
        const MenuNodeList::const_iterator  currItem;
    };
    
    //--------------------------------------------------------
    boost::optional<CurrentMenuNode> findCurrentNode(const MenuManager::MenuCursor& cursor)
    {
        if (cursor.navigationStack.empty())
        {
            return boost::none;
        }
        
        const auto& nodes = cursor.navigationStack.top()->getChildren();
        
        return CurrentMenuNode {
            nodes,
            std::find_if(nodes.begin(), nodes.end(), [&](const MenuNode& n) { return &n == cursor.currItem; })
        };
    }
}

//--------------------------------------------------------
void MenuManager::moveSelectionUp()
{
    auto currIt = findCurrentNode(m_Cursor);
    if (!currIt)
    {
        return;
    }
    
    if (currIt->currItem != currIt->nodes.begin() && currIt->currItem != currIt->nodes.end())
    {
        auto it = currIt->currItem;
        --it;
        highlightItem(*it);
    }
}

//--------------------------------------------------------
void MenuManager::moveSelectionDown()
{
    auto currIt = findCurrentNode(m_Cursor);
    if (!currIt)
    {
        return;
    }
    
    if (currIt->currItem != currIt->nodes.end())
    {
        auto it = currIt->currItem;
        ++it;
        if (it != currIt->nodes.end())
        {
            highlightItem(*it);
        }
    }
}

//--------------------------------------------------------
void MenuManager::actionSelection()
{
    if (m_Cursor.currItem->getHasSubMenu())
    {
        enterMenu(*m_Cursor.currItem);
    }
    else
    {
        m_Callback.itemWithTagActioned(m_Cursor.currItem->getTag());
    }
}

//--------------------------------------------------------
void MenuManager::navigateBack()
{
    if (m_Cursor.navigationStack.size() > 1)
    {
        m_Cursor.navigationStack.pop();
        enterMenu(*m_Cursor.navigationStack.top());
    }
}

//--------------------------------------------------------
void MenuManager::actionMenuNodeAtPoint(const PGPoint& pt)
{
    if (!m_Layer)
    {
        return;
    }
    
    auto currIt = findCurrentNode(m_Cursor);
    if (!currIt)
    {
        return;
    }

    auto textNodes = m_Layer->findNodesAtPoint(pt.x, pt.y);
    if (textNodes.empty())
    {
        return;
    }
    
    auto tag = textNodes.front()->getUserDataInt(kTag);

    const auto& menuNodes = currIt->nodes;
    auto menuNodeWithTagIt = std::find_if(menuNodes.begin(), menuNodes.end(), [&tag](const auto& n) { return n.getTag() == tag; });
    
    if (menuNodeWithTagIt != menuNodes.end())
    {
        highlightItem(*menuNodeWithTagIt);
        actionSelection();
    }
}

//--------------------------------------------------------
void MenuManager::enterMenu(const MenuNode& node)
{
    m_Cursor.navigationStack.push(&node);

    presentOnScene(node);

    if (!node.getChildren().empty())
    {
        highlightItem(node.getChildren().front());
    }
    else
    {
        m_Cursor.currItem = nullptr;
    }
}

//--------------------------------------------------------
void MenuManager::presentOnScene(const MenuNode& parentNode)
{
    m_Layer->clearChildren();

    auto frame = m_Scene.getSceneSize();
    
    double yPadding = 0.2 * frame.height;
    double availableHeight = (frame.height - (yPadding * 2));
    
    const auto& nodes = parentNode.getChildren();
    int nthNode = 0;
    for (const auto& node : nodes)
    {
        const auto nodeCount = std::max((size_t)1, nodes.size() - 1);
    
        auto x = (frame.width / 2.0);
        auto y = frame.height - yPadding - ((availableHeight / (double)nodeCount) * (double)nthNode);
        
        auto itemNode = createMenuTextNode(node);
        
        itemNode->setPosition(PGPoint(x, y));
        
        m_Layer->addChild(itemNode);
        
        ++nthNode;
    }
}

//--------------------------------------------------------
void MenuManager::highlightItem(const MenuNode& node)
{
    m_Cursor.currItem = &node;
    
    for (auto* itemNode : m_Layer->getChildren())
    {
        if (itemNode->getUserDataInt(kTag) == node.getTag())
        {
            itemNode->setColour(1, 0, 0, 1);
        }
        else
        {
            itemNode->removeColour();
        }
    }
}

}
